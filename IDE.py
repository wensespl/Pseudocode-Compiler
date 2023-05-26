from tkinter import Tk, StringVar, Text, Menu, END
from tkinter.ttk import Frame, Label, Entry, Button
from tkinter.scrolledtext import ScrolledText
from tkinter.messagebox import showwarning
from tkinter.filedialog import askopenfilename, asksaveasfilename
import re
from tkterminal import Terminal


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
    ['(^| )(SI|ENTONCES|SINO|FINSI)($| )', keywords4],
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
        
        self.menu_bar.add_cascade(label='File', menu=self.file_bar)

        self.container.config(menu=self.menu_bar)

        self.edit_area = Text(
            self, background=background2, foreground=normal, insertbackground=normal, borderwidth=10, relief='flat', font=font)
        self.edit_area.pack(fill='both', expand=1)
        
        self.edit_area.bind('<KeyRelease>', self.changes)
        
        self.edit_area.bind('<Control-s>', self.auto_save_file)

        # self.terminal = Terminal(self, borderwidth=10,
        #                          relief='flat', background='Black', foreground='White')
        # self.terminal.shell = True
        # self.terminal.pack(expand=True, fill='both')
    
    def changes(self, event=None):
        if self.edit_area.get(1.0, END) == self.previous_text:
            return
        
        for tag in self.edit_area.tag_names():
            self.edit_area.tag_remove(tag, 1.0, END)
        # Add tags where the search_re function found the pattern
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
    
    def auto_save_file(self):
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
