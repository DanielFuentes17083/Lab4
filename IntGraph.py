from tkinter import * #https://likegeeks.com/es/ejemplos-de-la-gui-de-python/
import serial #https://github.com/JALR0701/Laboratorio-4/blob/master/GUI.py
import struct
import time

while(1): #Se inicializa la conexion con el puerto
    while(1):
        try:
            numero = str(int(input(">  COM: ")))
            port = "com" + numero
            break
        except:
            print ("Enter a numeric value")
    try:
        data = serial.Serial(port, baudrate = 9600, timeout=1500)
        break
    except:
        print("Unable to open port")


gui = Tk(className='Comunicacion serial')
# set window size
gui.geometry("900x600")

puerto = Label(gui, text = "COM:" + numero, font = ("Arial", 25))
BT1 = Button(gui, text='Enviar valor')
entry = Entry(gui, width=20)
label1 = label(gui, text='Ingrese el valor del contador')

puerto.pack()
label1.place(x=50, y=25)
BT1.place(x=100, y=100)
entry.place(x=100, y=50)

def ENVIO():
    try:
        contador = int(entry.get())
        if contador < 255 and contador > 0:
            data.write(struct.pack('>B',contador))
        else:
            messagebox.showerror('Error', 'el valor no puede ser mayor a 255 o menor que 0')
    except:
        messagebox.showerror('Error', 'Ingrese un numero entero')

gui.mainloop()
