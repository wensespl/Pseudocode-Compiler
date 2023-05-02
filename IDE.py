from tkinter import Tk, StringVar, Text, Menu
from tkinter.ttk import Frame, Label, Entry, Button
from tkinter.scrolledtext import ScrolledText
from tkinter.messagebox import showwarning
import re
import ctypes
from tkterminal import Terminal

ctypes.windll.shcore.SetProcessDpiAwareness(True)


class IDEFrame(Frame):
    def __init__(self, container):
        super().__init__(container)
        self.container = container

        self.__config()

    def __config(self):
        self.menu_bar = Menu(self.container)

        self.file_bar = Menu(self.menu_bar, tearoff=0)
        self.file_bar.add_command(label='Open file')
        self.menu_bar.add_cascade(label='File', menu=self.file_bar)

        self.container.config(menu=self.menu_bar)

        self.edit_area = ScrolledText(
            self, borderwidth=30, relief='flat', font='Consolas 15')
        self.edit_area.pack(fill='both', expand=1)

        self.terminal = Terminal(self, borderwidth=30, relief='flat')
        self.terminal.shell = True
        self.terminal.pack(expand=True, fill='both')


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
