# Authors: Antonios Glioumpas & Nikiforos Paraskevopoulos
# version: 4
# date : 20 March 2015
#
# Description:
# This script is used in order to identify each button of the Arduino Bluetooth RC Car App, to which ascii value it corresponds

import pyxhook
import time
import serial
from time import sleep

letter = "duth"
gripperState = False # initialize open
elbowState = False # initialize down
light = False # initialize closed

 
bluetoothSerial = serial.Serial( "/dev/rfcomm0", baudrate=9600 )
time.sleep(3)
#bluetoothSerial = serial.Serial("/org/bluez/844/hci0/dev_20_14_12_08_16_91",baudrate=9600)


#This function is called every time a key is presssed
def kbevent( event ):
    #print key info
    #print event
    
    #If the ascii value matches spacebar, terminate the while loop
    """
    if event.Ascii == 32:
        global running
        runningr = False
    letter = event.Ascii
    print letter
    """
    global gripperState
    global elbowState
    global light
    global bluetoothSerial
    global letter
    # Vehicle Control
    letter = event.Ascii
    if letter == 119:
            #forward
            bluetoothSerial.write(str(102))
            print " move forward"
    elif letter == 115:
                    #backward
            bluetoothSerial.write(str(98))
            print " move backward"
    elif letter == 97:
                    #left
            bluetoothSerial.write(str(108))
            print " move left "
    elif letter == 100:
                    #right
            bluetoothSerial.write(str(114))
            print " move right"

   

    #elbow Control
    if letter == 101:
        if (elbowState == False):
            elbowState = True
            bluetoothSerial.write(str(117))
            print " elbow up"
        else:
            elbowState = False
            bluetoothSerial.write(str(116))
            print " elbow down"

    #gripper Control
    if letter == 113:
        if (gripperState == False):
            gripperState = True
            bluetoothSerial.write(str(119))
            print " gripper open"
        else:
            gripperState = False
            bluetoothSerial.write(str(118))
            print " gripper close"

    #Light Control
    if letter == 32:
        if (light == False):
            light = True
            bluetoothSerial.write(str(120))
            print " light open"
        else :
            light = False
            bluetoothSerial.write(str(121))
            print " light close"

    #Camera Control
    if letter == 105:
            bluetoothSerial.write(str(112))
            print " camera UP"
    elif letter == 107:
            bluetoothSerial.write(str(113))
            print " camera DOWN"
    elif letter == 108:
            bluetoothSerial.write(str(104))
            print " camera LEFT"
    elif letter == 106:
            bluetoothSerial.write(str(105))
            print " camera RIGHT"

    if letter == 96:
            bluetoothSerial.write(str(0))
    elif letter  == 49:
            bluetoothSerial.write(str(1))
    elif letter == 50:
            bluetoothSerial.write(str(2))
    elif letter == 51:
            bluetoothSerial.write(str(3))
    elif letter == 52:
            bluetoothSerial.write(str(4))
    elif letter == 53:
            bluetoothSerial.write(str(5))
    elif letter == 54:
            bluetoothSerial.write(str(6))
    elif letter == 55:
            bluetoothSerial.write(str(7))
    elif letter == 56:
            bluetoothSerial.write(str(8))
    elif letter == 57:
            bluetoothSerial.write(str(9))
    elif letter == 102:
            bluetoothSerial.write(str(10))
""" I:mprosta, K:piso,J:arister,L:deksia"""


#Create hookmanager
hookman = pyxhook.HookManager()
#Define our callback to fire when a key is pressed down
hookman.KeyDown = kbevent
#Hook the keyboard
a= hookman.HookKeyboard()
#Start our listener
b =hookman.start()

#Create a loop to keep the application running
running = True
while running:
    time.sleep(0.1)

#Close the listener when we are done
hookman.cancel()

""" motor movement --> forward:W, back:S, left:A, right:D
    open-close gripper: Q
    up-down elbow: E
    movement kamera --> up:I, down:K, left:J, right:L
    led--> turn on, turn off :space
    velocities :(0-9)  0 will be i ~. full speed at 0 
    
"""



