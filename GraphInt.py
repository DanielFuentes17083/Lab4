from tkinter import * #https://likegeeks.com/es/ejemplos-de-la-gui-de-python/
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
gui.geometry("900x600")
pot1 = StingVar()
pot2 = StingVar()
pot1.set("0 V")
pot2.set("0 V")

puerto = Label(gui, text = "COM:" + numero, font = ("Arial", 25))
BT1 = Button(gui, text='Enviar valor')
entry = Entry(gui, width=20)
label1 = label(gui, text='Ingrese el valor del contador')
label2 = label(gui, text='S1:', font = ("Arial", 25))
label3 = label(gui, text='S2:', font = ("Arial", 25))
label4 = label(gui, textvariable=pot1, font = ("Arial", 25))
label5 = label(gui, textvariable=pot2, font = ("Arial", 25))

puerto.pack()
label1.grid(column=5, row=3)
BT1.grid(column=5, row=5)
entry.grid(column=5, row=4)
label2.grid(column=1, row=3)
label3.grid(column=3, row=3)
label4.grid(column=1, row=4)
label5.grid(column=3, row=4)

def ENVIO():
    try:
        contador = int(entry.get())
        if contador < 255 and contador > 0:
            data.write(struct.pack('>B',contador))
        else:
            messagebox.showerror('Error', 'el valor no puede ser mayor a 255 o menor que 0')
    except:
        messagebox.showerror('Error', 'Ingrese un numero entero')

def getSerial():
    p1 = ord(data.read())
    p2 = ord(data.read())
    conv1 = str("{0.2f}".format(p1*(5/255)) + " V"
    conv2 = str("{0.2f}".format(p2*(5/255)) + " V"
    pot1.set(conv1)
    pot2.set(conv2)
    gui.after(10,getSerial)

gui.after(10,getSerial)
gui.mainloop()
