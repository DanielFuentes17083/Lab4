from tkinter import * #https://likegeeks.com/es/ejemplos-de-la-gui-de-python/
from tkinter import messagebox
import serial 
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
gui.geometry("550x250")
pot1 = StringVar()
pot2 = StringVar()
pot1.set("0 V")
pot2.set("0 V")



puerto = Label(gui, text = "COM:" + numero, font = ("Arial", 25))
entry = Entry(gui, width=32)
def ENVIO():
    contador = entry.get()
    if contador != "":
        try:
            contador = int(entry.get())
            if contador <= 255 and contador >= 0:
                data.write(struct.pack('>B',contador))
            else:
                messagebox.showerror(title='Error', message='el valor no puede ser mayor a 255 o menor que 0')
        except:
            messagebox.showerror(title='Error', message='Ingrese un numero entero')
    else:
        data.write(struct.pack('>B',0))
BT1 = Button(gui, text='Enviar valor', command=ENVIO)
label1 = Label(gui, text='Ingrese el valor del contador', font = ("Arial", 12))
label2 = Label(gui, text='S1:', font = ("Arial", 25))
label3 = Label(gui, text='S2:', font = ("Arial", 25))
label4 = Label(gui, textvariable=pot1, font = ("Arial", 25))
label5 = Label(gui, textvariable=pot2, font = ("Arial", 25))

puerto.pack()
label1.place(x=300, y=70)

label2.place(x=50, y=60)
label3.place(x=200, y=60)
label4.place(x=25, y=150)
label5.place(x=180, y=150)
entry.place(x=300, y=110)
BT1.place(x=420, y=160)


def getSerial():
    p1 = ord(data.read())
    p2 = ord(data.read())
    m1 = "{0:.2f}".format(p1 *(5/255))
    m2 = "{0:.2f}".format(p2 *(5/255))
    pot1.set(str(m1)+" V")
    pot2.set(str(m2)+" V")
    gui.after(10,getSerial)

gui.after(10,getSerial)
gui.mainloop()
