Title:    BarBot
Author: Peter

[TITLE]
#Automatic Drink Mixing Machine

This system is designed to control the cocktail machine with Zaber Scriptrunner and Arduino. This machine consists of an Arduino Uno, an EasyDriver v4.5 motor driver, an LED strip, a STM100 stepper motor, two Zaber linear stages (500mm and 750mm) and one Zaber lift stage (20mm). The machine will mix up to 4 kinds of alcohols loaded on the drink dispenser to make cocktails. It can stir the drink automatically as well.

# Hardware Required
* Arduino Uno
* EasyDriver v4.5
* STM100 Stepper Motor
* Digital RGB LED Strip -- LPD8806
* Zaber 750mm Linear Stager -- T-LST0750B
* Zaber 500mm Linear Stager -- T-LST0500B
* Zaber 20mm Lift Stager -- VSR20A-T3
* Zaber Dual Axis Stepper Motor Controllers -- A-MCB2
* Zaber Stepper Motor Controller -- A-MCA

# Software Required
* Zaber Console 2.0.10 [Download](http://www.zaber.com/support/software.php?file=zaber_console_installer)

_ Note: The ClickOnce version cannot be used _

* Arduino IDE [Download](https://www.arduino.cc/en/Main/Software)
* LPD8806 Library

#Wiring
* EasyDriver -> Arduino
* M+ -> 12V power supply
* GND -> 12V power supply ground & Arduino ground
* Motor A1 -> Red wire on stepper motor
* Motor A2 -> Green wire
* Motor B1 -> Yellow wire
* Motor B2 -> Black wire
* DIR -> Arduino Pin 8
* STP -> Arduino Pin 9

* Button -> Arduino
* Vin -> 3.3V
* GND -> GND on Arduino
* Pin -> Arduino Pin 7

* LED strip -> Arduino
* Power Socket -> 12V power supply
* GND (purple wire) -> Arduino ground
* CLK (green wire) -> Arduino Pin 2
* DATA (blue wire) -> Arduino Pin 4

* Connect two linear stagers (500mm & 750mm) to A-MCB2
* Connect the lift stager to A-MCA
* Connect A-MCA to A-MCB2
* Connect A-MCB2 to computer
* Connect Arduino to computer

# Program pre-setup
* Install Zaber Console [Details &amp; Downloads](http://www.zaber.com/wiki/Software/Zaber_Console)
* Install Integrated USB Driver (Create virtual serial port) [Details &amp; Downloads](http://www.zaber.com/wiki/Software/Integrated_USB_Driver)
* Add the Zaber Console directory to your Windows path.
1. Open System Properties (Win+Pause)
2. Switch to the Advanced tab
3. Click Environment Variables
4. Select PATH in the System variables section
5. Click Edit
6. Add a semicolon to the end of the list and then add Zaber Console's path.
* For example, pretend the path is already this: C:\Program Files\MSOffice
If you installed in the default location, you would change it to this: C:\Program Files\MSOffice;C:\Program Files\Zaber Technologies\Zaber Console 1.2.X
Click OK. Click OK.
* Connect the motor controllers and Arduino to the computer If you haven't
* Check their port name in the device manager
* Change the port name in the Port_communication.cs and Button_Standby.cs

# How to run the program 
1. Connect motor controllers and Arduino to the computer
2. Turn on the power
3. Run Zaber Console, home all axes
4. Exit Zaber Console
5. Run ConsoleApplication1.exe
6. Push the button on the breadboard
7. If a new command window prompts out, it means the program has received the signal 
and will execute the script after several seconds.
8. Wait for the whole process. (approx 1 min)
9. If you want to run the program again, just push the button again




