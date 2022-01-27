# Belt-Tensioner-Robot-Servo
Sim Racing Belt Tensioner using robots hobby servos and SimHub

Based on the original project:

author=blekenbleu,
title = SimHub Custom serial device for Blue Pill
year =2021
url = https://blekenbleu.github.io/Arduino/
Description: https://blekenbleu.github.io/Arduino/SimHubCustomSerial
Original Arduino Blue Pill scetch: https://github.com/blekenbleu/blekenbleu.github.io/tree/master/Arduino/Blue_ASCII_Servo
Original SimHub Profile: https://blekenbleu.github.io/Arduino/proxy_G.shsds.txt

Youtube demo of my belt tensioner: https://www.youtube.com/watch?v=9a0rFGwfBp4

BOM:
- Arduino Nano
- 2x Twin Arm servo, 180 degrees, 60KG, 8.4V; full metal brackets - DSServo RDS5160 SSG 60kg 8.4v High Voltage Torque Stainless Steel Gear Digital Servo For RC Model Robot Arm Arduino DIY Industry (from Aliexpress)
- XL4005 5A 75W XL4015 DC-DC XL6009 Power Supply Module Boost Buck DC to DC Adjustable Step Up Step Down Converter Module

Optional:
- 2022 New 6pcs 16V 16.6F Super Capacitor High Current 2.7V 100F Double Row Ultracapacitor
- XT60 connectors
- Volt indicators
- Automotive fuse


Description:

Utilizes two Robot Hobby servos , 60KG each, driven by SimHub Custom profile. Modifications to origina blackenbleu code include:

Blue_ASCII_Servo.ino (Arduino sketch, tested with Nano and Pro Micro):
- Modified output signal to reference Digital Out pins on arduino Nano

SimHub Belt Tensioner.shsds
- Modified to use general Acceleration values (AccelerationSway;GlobalAccelerationG), which are supported by more games. Original was based on GameRawData.Physics.AccG01 and GameRawData.Physics.AccG03.
- Added "Reste" Function - based on SimHub value "IsGameRunning" - checks if game is running, otherwise leaves belts untensioned. Original profile in Dirt Rally 2.0 was laways leaving residue tension in belts after race, which was nulled at the beginnning of next race, keeping belts in menus always tensioned.


Servos:

My seatbelt tensioner is built on 60KG servos. Originally started with 35KG, which is more than enough stength, but they burned out very fast - they cannot support working on full load under such circumstances.

The 60kg serwos are 180 degrees, the range I am using them is only 50 degrees. More than 60 they obtail full load, which translates to 4A consumption per servo, also it reallyhurts my sholders at this stage, whcih is better to be avoided. I ordered the 180ddegree ones for ease of configuration in SimHub, but with original brackets rarely they will  used more than 90 degrees of rotation. Also ordered full metal brackets and ball bearing rollers - they are pretty strong and you need the structural integrity.


Power Supply:

Servos are driven at 8.2Vm which is little less than their advertised maximum of 8.4V. This gives very fast response, also quiet operation.
I have added Supercapacitors to smoothen the servo responese time, also load on the Power Supply DC-DC convertor. Supercapacitors requite ballance circuit, chepest option was to buy 6 in series and cut them in half. Every capacitor has 2.7V nominal so 3 in series are enought for driving the servos.

Supercapacitors charge for less than minute, initial current is 4A at about 5 seconds, then drops rapidly. The 5A module is still holding OK. I ampowering it with 12V from anothe Powersupply, used for mi Bass shakers + wind sim + aRGB lights.


Servo current draw:

Full lock - 4A (measured 3.8-42)<br>
Normal lock (without hurting shoulders) - about 2-2.2A


Mechanical configuration:

Servos were mechanically adjusted after powering them up (without conection to PC) to reflect 0 degree angle at the most realxt position Iwant them in.
Servos are mounted directly to 3030 Aluminum profile attached to the bottom of my seat using the supplied metal brackets. Extensive testing proved this is enough for structural integrity.


Software configuration:

Sketch loaded to Arduino Nano, connected as Custom Serial Device in SimHub.
Initial servo position, max tension - set in SimHub Profile. 
