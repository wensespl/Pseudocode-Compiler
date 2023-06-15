from tkinter import Tk, Text, Menu, Toplevel, END
from tkinter.ttk import Frame
from tkinter.messagebox import showwarning
from tkinter.filedialog import askopenfilename, asksaveasfilename
import re
import subprocess
import os
import shlex
from tkterminal import Terminal

from Parser import Parser
from IRGenerator import Generator


def rgbToHex(rgb):
    return "#%02x%02x%02x" % rgb

normal = rgbToHex((213, 206, 217))
keywords1 = rgbToHex((199, 77, 237))
keywords2 = rgbToHex((249, 38, 114))
keywords3 = rgbToHex((238, 93, 67))
keywords4 = rgbToHex((124, 183, 255))
keywords5 = rgbToHex((150, 224, 114))
keywords6 = rgbToHex((255, 0, 170))
comments = rgbToHex((160, 161, 167))
string = rgbToHex((255, 230, 109))
numbers = rgbToHex((243, 156, 18))
variables = rgbToHex((0, 232, 198))
function = rgbToHex((95, 211, 234))
background1 = rgbToHex((42, 42, 42))
background2 = rgbToHex((35, 38, 46))
font = 'Consolas 12'

repl = [
    [r'(\+|-|\*|/|=|%|<|<=|>|>=|==|<>)', keywords3],
    [r'\d+(\.\d*)?', numbers],
    [r'[a-zA-Z_][a-zA-Z0-9_]*', variables],
    ['(ENTRADA|SALIDA)', keywords1],
    ['(ENTERO|DECIMAL)', keywords1],
    ['(SUBRUTINA|FINSUBRUTINA)', keywords4],
    ['(DEVOLVER)', keywords6],
    ['(^| )(ENTONCES|SINO|SI|FINSI)($| )', keywords4],
    ['(MIENTRAS|HACER|FINMIENTRAS)', keywords4],
    ['(PARA|HASTA|FINPARA)', keywords4],
    [r'".*?"', string],
    ['#.*?$', comments]
]

class IDEFrame(Frame):
    def __init__(self, container):
        super().__init__(container)
        self.container = container
        self.previous_text = ''
        self.actual_filepath = ''

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

        self.container.config(menu=self.menu_bar)

        self.edit_area = Text(
            self, background=background2, foreground=normal, insertbackground=normal, borderwidth=10, relief='flat', font=font)
        self.edit_area.pack(fill='both', expand=1)
        
        self.edit_area.bind('<KeyRelease>', self.changes)
        
        self.edit_area.bind('<Control-s>', self.auto_save_file)

        self.terminal = Terminal(self, borderwidth=10,
                                 relief='flat', background='Black', foreground='White')
        self.terminal.shell = True
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
        # self.bison_window = Toplevel(self.container)
        pathexe = os.path.abspath("project_bison\\a.exe")
        pathfile = self.actual_filepath
        # pathfile = os.path.abspath("examples\\test.spl")
        out = subprocess.run([pathexe, '<', pathfile], shell=True, capture_output=True)
        print(out.stdout.decode("utf-8"))
    
    def changes(self, event=None):
        if self.edit_area.get(1.0, END) == self.previous_text:
            return
        
        for tag in self.edit_area.tag_names():
            self.edit_area.tag_remove(tag, 1.0, END)
        
        i = 0
        for pattern, color in repl:
            for start, end in self.search_re(pattern, self.edit_area.get(1.0, END)):
                self.edit_area.tag_add(f'{i}', start, end)
                self.edit_area.tag_config(f'{i}', foreground=color)
                i += 1
                
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
