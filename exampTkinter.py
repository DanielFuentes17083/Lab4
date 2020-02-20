from tkinter import *

gui = Tk(className='Interfaz')
# set window size
gui.geometry("900x600")

BT1 = Button(gui, text='Enviar valor')
entry = Entry(gui, width=20)
BT1.place(x=100, y=100)
entry.place(x=100, y=50)

gui.mainloop()
