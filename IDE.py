from tkinter import Tk, Text, Menu, Toplevel, END
from tkinter.ttk import Frame
from tkinter.messagebox import showwarning
from tkinter.filedialog import askopenfilename, asksaveasfilename
from pathlib import Path
from tkterminal import Terminal
import re, subprocess

from Parser import Parser
from IRGenerator import Generator


class Helper():
    def __init__(self) -> None:
        self.change_theme1()
        self.fuente_font = 'Consolas 16'  
    
    def change_theme1(self):
        self.color_normal = self.rgbToHex((213, 206, 217))
        self.color_keywords1 = self.rgbToHex((199, 77, 237))
        # keywords2 = rgbToHex((249, 38, 114))
        self.color_keywords3 = self.rgbToHex((238, 93, 67))
        self.color_keywords4 = self.rgbToHex((124, 183, 255))
        # keywords5 = rgbToHex((150, 224, 114))
        self.color_keywords6 = self.rgbToHex((255, 0, 170))
        self.color_comments = self.rgbToHex((160, 161, 167))
        self.color_string = self.rgbToHex((255, 230, 109))
        self.color_numbers = self.rgbToHex((243, 156, 18))
        self.color_variables = self.rgbToHex((0, 232, 198))
        # function = rgbToHex((95, 211, 234))
        # background1 = rgbToHex((42, 42, 42))
        self.color_background2 = self.rgbToHex((35, 38, 46))
        self.change_repl()
    
    def change_theme2(self):
        self.color_normal = self.rgbToHex((0, 0, 0))
        self.color_keywords1 = self.rgbToHex((0, 0, 0))
        # keywords2 = rgbToHex((249, 38, 114))
        self.color_keywords3 = self.rgbToHex((0, 0, 0))
        self.color_keywords4 = self.rgbToHex((0, 0, 0))
        # keywords5 = rgbToHex((150, 224, 114))
        self.color_keywords6 = self.rgbToHex((0, 0, 0))
        self.color_comments = self.rgbToHex((0, 0, 0))
        self.color_string = self.rgbToHex((0, 0, 0))
        self.color_numbers = self.rgbToHex((0, 0, 0))
        self.color_variables = self.rgbToHex((0, 0, 0))
        # function = rgbToHex((95, 211, 234))
        # background1 = rgbToHex((42, 42, 42))
        self.color_background2 = self.rgbToHex((255, 255, 255))
        self.change_repl()
    
    def change_repl(self):
        self.repl = [
                [r'(\+|-|\*|/|=|%|<|<=|>|>=|==|<>)', self.color_keywords3],
                [r'\d+(\.\d*)?', self.color_numbers],
                [r'[a-zA-Z_][a-zA-Z0-9_]*', self.color_variables],
                ['(ENTRADA|SALIDA)', self.color_keywords1],
                ['(ENTERO|DECIMAL)', self.color_keywords1],
                ['(SUBRUTINA|FINSUBRUTINA)', self.color_keywords4],
                ['(DEVOLVER)', self.color_keywords6],
                ['(^| )(ENTONCES|SINO|SI|FINSI)($| )', self.color_keywords4],
                ['(MIENTRAS|HACER|FINMIENTRAS)', self.color_keywords4],
                ['(PARA|HASTA|FINPARA)', self.color_keywords4],
                [r'".*?"', self.color_string],
                ['#.*?$', self.color_comments]
            ]
    
    def rgbToHex(self,rgb):
        return "#%02x%02x%02x" % rgb

class IDEFrame(Frame):
    def __init__(self, container):
        super().__init__(container)
        self.container = container
        self.previous_text = ''
        self.actual_filepath = ''
        self.bison_window = None
        self.helper = Helper()
        self.theme_color = "black"

        self.__config()

    def __config(self):
        self.menu_bar = Menu(self.container)

        self.file_bar = Menu(self.menu_bar, tearoff=0)
        self.file_bar.add_command(label='Open file', command=self.open_file)
        self.file_bar.add_command(label='Save file', command=self.save_file)
        self.menu_bar.add_cascade(label='Archivo', menu=self.file_bar)
        
        self.compiler_bar = Menu(self.menu_bar, tearoff=0)
        self.compiler_bar.add_command(label='Ejecutar', command=self.execute)
        self.compiler_bar.add_command(label='Compilar', command=self.compile)
        self.menu_bar.add_cascade(label='Compilar', menu=self.compiler_bar)
        
        self.bison_bar = Menu(self.menu_bar, tearoff=0)
        self.bison_bar.add_command(label='Ejecutar', command=self.run_bison)
        self.menu_bar.add_cascade(label='Bison', menu=self.bison_bar)
        
        self.theme_bar = Menu(self.menu_bar, tearoff=0)
        self.theme_bar.add_command(label='Tema claro', command=self.change_theme2)
        self.theme_bar.add_command(label='Tema oscuro', command=self.change_theme1)
        self.menu_bar.add_cascade(label='Tema de color', menu=self.theme_bar)

        self.container.config(menu=self.menu_bar)

        self.edit_area = Text(
                                self, 
                                background=self.helper.color_background2, 
                                foreground=self.helper.color_normal, 
                                insertbackground=self.helper.color_normal, 
                                borderwidth=10, 
                                relief='flat', 
                                font=self.helper.fuente_font
                                )
        self.edit_area.pack(fill='both', expand=1)
        
        self.edit_area.bind('<KeyRelease>', self.changes)
        
        self.edit_area.bind('<Control-s>', self.auto_save_file)

        self.terminal = Terminal(self, borderwidth=10, relief='flat', foreground='#000000', font=self.helper.fuente_font)
        self.terminal.shell = True
        self.terminal.tag_config("output", foreground='#000000')
        self.terminal.basename = "SPL-Compiler$"
        self.terminal.tag_config("basename", foreground='#FF007F')
        self.terminal.pack(expand=True, fill='both')
    
    def gen_outputll(self):
        filename = self.actual_filepath
        output = "output.ll"
        
        input_file = open(filename)
        lines = [line.lstrip() for _, line in enumerate(input_file) if line.strip()]
        lines[-1] = lines[-1].rstrip()
        input_file.close()

        text = ''.join(lines)
        
        ast = Parser().parse(text)
            
        ir = Generator().generate(ast, output)
        
        output_file = open(output,"w+")
        output_file.write(str(ir))
        output_file.close()
    
    def execute(self):
        if not self.actual_filepath:
            showwarning("Warning", "Debe tener un archivo activo")
            return
        self.gen_outputll()
        self.terminal.run_command('tools\lli.exe output.ll')
    
    def compile(self):
        if not self.actual_filepath:
            showwarning("Warning", "Debe tener un archivo activo")
            return
        self.gen_outputll()
        self.terminal.run_command('clang output.ll')
    
    def run_bison(self):
        if not self.actual_filepath:
            showwarning("Warning", "Debe tener un archivo activo")
            return
        
        if self.bison_window is not None:
            self.bison_window.destroy()
        
        self.bison_window = Toplevel(self.container)
        
        window_width = 800
        window_height = 800

        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()

        center_x = int(screen_width/2 - window_width/2)
        center_y = int(screen_height/2 - window_height/2)

        self.bison_window.geometry(f"{window_width}x{window_height}+{center_x}+{center_y}")
        self.bison_window.resizable(True, True)
        
        edit_area = Text(
            self.bison_window, borderwidth=10, relief='flat', font=self.helper.fuente_font)
        edit_area.pack(fill='both', expand=1)
        
        pathexe = Path("project_bison/SPL.exe")
        pathfile = self.actual_filepath
        
        output = subprocess.run([pathexe, '<', pathfile], shell=True, capture_output=True)
        
        edit_area.insert(1.0, output.stdout.decode("utf-8"))
        
    def change_theme1(self):
        if self.theme_color == "black":
            return
        
        self.helper.change_theme1()
        self.configure_edit_area()
        self.theme_color = "black"
    
    def change_theme2(self):
        if self.theme_color == "white":
            return
        
        self.helper.change_theme2()
        self.configure_edit_area()
        
        self.theme_color = "white"

    def configure_edit_area(self):
        self.edit_area.configure(
            background=self.helper.color_background2, 
            foreground=self.helper.color_normal, 
            insertbackground=self.helper.color_normal,
            font=self.helper.fuente_font
            )
        self.change_tags()
    
    def change_tags(self):
        for tag in self.edit_area.tag_names():
            self.edit_area.tag_remove(tag, 1.0, END)
        
        i = 0
        for pattern, color in self.helper.repl:
            for start, end in self.search_re(pattern, self.edit_area.get(1.0, END)):
                self.edit_area.tag_add(f'{i}', start, end)
                self.edit_area.tag_config(f'{i}', foreground=color)
                i += 1
    
    def changes(self, event=None):
        if self.edit_area.get(1.0, END) == self.previous_text:
            return
        
        self.change_tags()
                
        self.previous_text = self.edit_area.get(1.0, END)
    
    def search_re(self, pattern, text, groupid=0):
        matches = []

        text = text.splitlines()
        for i, line in enumerate(text):
            for match in re.finditer(pattern, line):
                matches.append(
                    (f"{i + 1}.{match.start()}", f"{i + 1}.{match.end()}")
                )

        return matches
    
    def open_file(self):
        filepath = askopenfilename(
            filetypes=[("Text Files", "*.spl"), ("All Files", "*.*")]
        )
        if not filepath:
            return
        self.edit_area.delete(1.0, END)
        with open(filepath, "r") as input_file:
            text = input_file.read()
            self.edit_area.insert(END, text)
        self.changes()
        self.container.title(f"Spanish Pseudocode Compiler - {filepath}")
        self.actual_filepath = filepath
    
    def save_file(self):
        filepath = asksaveasfilename(
            defaultextension="spl",
            filetypes=[("Text Files", "*.spl"), ("All Files", "*.*")],
        )
        if not filepath:
            return
        with open(filepath, "w") as output_file:
            text = self.edit_area.get(1.0, END)
            output_file.write(text)
        self.container.title(f"Spanish Pseudocode Compiler - {filepath}")
        self.actual_filepath = filepath
    
    def auto_save_file(self, event=None):
        if not self.actual_filepath:
            self.save_file()
            return
        with open(self.actual_filepath, "w") as output_file:
            text = self.edit_area.get(1.0, END)
            output_file.write(text)


class App(Tk):
    def __init__(self):
        super().__init__()

        self.__config()

        self.IDE_frame = IDEFrame(self)
        self.IDE_frame.pack(fill='both', expand=1, padx=5, pady=5)

    def __config(self):
        self.title("Spanish Pseudocode Compiler")

        window_width = 1000
        window_height = 800

        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()

        center_x = int(screen_width/2 - window_width/2)
        center_y = int(screen_height/2 - window_height/2)

        self.geometry(f"{window_width}x{window_height}+{center_x}+{center_y}")
        self.resizable(True, True)


if __name__ == "__main__":
    app = App()
    app.mainloop()
