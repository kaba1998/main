import sys
from tkinter import *
from tkinter import filedialog as fd

sys.path.append(
    "C:/Users/Aicha/Desktop/Lab3/x64/Release")

import Lab3 

def stop():
    Lab3.Quitter()
    root.destroy()


class UI(Frame):
    def __init__(self, parent=None, **options):
        Frame.__init__(self, parent, **options)
        self.pack()

        self.buttons = {}
        self.buttons["Open File"] = Button(
            self, text="Ouvrir un fichier", command=lambda: self.openFile())
        self.buttons["Play_Pause_video"] = Button(
            self, text="Play_Pause_video", state=DISABLED, command=Lab3.Play_Pause_video)
        self.buttons["Accelerate"] = Button(
            self, text="Acelerate", state=DISABLED, command=Lab3.Accelerate)
        self.buttons["Repeat"] = Button(
            self, text="Repeat", state=DISABLED, command=Lab3.Repeat)
        self.buttons["Quitter"] = Button(self, text="Quitter", command=stop)

        for button in self.buttons:
            self.buttons[button].pack(side=LEFT, fill=BOTH)

    def openFile(self):
        path = fd.askopenfilename()
        Lab3.Start("", path)
        self.buttons["Open File"].config(state=DISABLED)
        self.buttons["Play_Pause_video"].config(state=NORMAL)
        self.buttons["Accelerate"].config(state=NORMAL)
        self.buttons["Repeat"].config(state=NORMAL)



root = Tk()
UI(root)
root.protocol("WM_DELETE_WINDOW", stop)
root.mainloop()
