from tkinter import Tk, StringVar, Text, Menu
from tkinter.ttk import Frame, Label, Entry, Button
from tkinter.scrolledtext import ScrolledText
from tkinter.messagebox import showwarning
import re
from tkterminal import Terminal


# Convert an RGB tuple to a HEX string using the % Operator
# 02 means print 2 characters
# x means hexadecimal
def rgbToHex(rgb):
    return "#%02x%02x%02x" % rgb

# Define colors for the variouse types of tokens
normal = rgbToHex((234, 234, 234))
keywords = rgbToHex((234, 95, 95))
comments = rgbToHex((95, 234, 165))
string = rgbToHex((234, 162, 95))
function = rgbToHex((95, 211, 234))
background = rgbToHex((42, 42, 42))
font = 'Consolas 12'

# Define a list of Regex Pattern that should be colored in a certain way
repl = [
    ['(^| )(ENTERO|DECIMAL|ENTRADA|SALIDA|SUBRUTINA|FINSUBRUTINA|DEVOLVER|SI|ENTONCES|SINO|FINSI|MIENTRAS|HACER|FINMIENTRAS|PARA|HASTA|FINPARA)($| )', keywords],
    ['".*?"', string],
    ['#.*?$', comments],
]

class IDEFrame(Frame):
    def __init__(self, container):
        super().__init__(container)
        self.container = container
        self.previousText = ''

        self.__config()

    def __config(self):
        self.menu_bar = Menu(self.container)

        self.file_bar = Menu(self.menu_bar, tearoff=0)
        self.file_bar.add_command(label='Open file')
        self.menu_bar.add_cascade(label='File', menu=self.file_bar)

        self.container.config(menu=self.menu_bar)

        self.edit_area = Text(
            self, background=background, foreground=normal, insertbackground=normal, borderwidth=10, relief='flat', font=font)
        self.edit_area.pack(fill='both', expand=1)
        
        # Bind the KeyRelase to the Changes Function
        self.edit_area.bind('<KeyRelease>', self.changes)
        
        # Bind Control + R to the exec function
        # self.bind('<Control-r>', execute)

        self.terminal = Terminal(self, borderwidth=10,
                                 relief='flat', background='Black', foreground='White')
        self.terminal.shell = True
        self.terminal.pack(expand=True, fill='both')
    
    def changes(self, event=None):
        # If actually no changes have been made stop / return the function
        if self.edit_area.get('1.0', "end") == self.previousText:
            return
        for tag in self.edit_area.tag_names():
            self.edit_area.tag_remove(tag, "1.0", "end")
        # Add tags where the search_re function found the pattern
        i = 0
        for pattern, color in repl:
            for start, end in self.search_re(pattern, self.edit_area.get('1.0', 'end')):
                self.edit_area.tag_add(f'{i}', start, end)
                self.edit_area.tag_config(f'{i}', foreground=color)

                i+=1
        self.previousText = self.edit_area.get('1.0', 'end')
    
    def search_re(self, pattern, text, groupid=0):
        matches = []

        text = text.splitlines()
        for i, line in enumerate(text):
            for match in re.finditer(pattern, line):

                matches.append(
                    (f"{i + 1}.{match.start()}", f"{i + 1}.{match.end()}")
                )

        return matches


class App(Tk):
    def __init__(self):
        super().__init__()

        self.__config()

        self.IDE_frame = IDEFrame(self)
        self.IDE_frame.pack(fill='both', expand=1, padx=5, pady=5)

    def __config(self):
        self.title("Spanish Pseudocode Compiler (IDE)")

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
