## Functions for each mechatronics components
#### 2 Arduino UNO 
* Interface all the mechatronics components

#### 1 12V 5A Power Supply
* Main power source

#### 2 Step down buck converters
* Convert 12V to 5V to power Arduino
* Convert 12V to 7.3V to power 360 Servo Motor

#### Resistors (330 ohms & 10k ohms)

#### Potentiometer
* Adjust the brightness and clarity for the LCD

### Air Purifier System:
12V 2A Fan
* Circulate and purify the air that is going out of the HEPA filter 
<img width="154" alt="image" src="https://user-images.githubusercontent.com/122852792/229263791-ffd81eff-5565-4ffe-bd74-0fa82a1155f2.png">

### Sanitiser System:
#### 1 Piezo Buzzer
* Buzz once when the sanitiser system is on
* Buzz once when manual detection is succesful
* Buzz thrice before sanitisation occurs

#### 2 Latching Pushbutton:
* ON/OFF the sanitiser system
* Change the mode of the sanitiser system (manual and automatic)
<img width="136" alt="image" src="https://user-images.githubusercontent.com/122852792/229263868-97f6048d-a20a-47e0-a189-97ad9efb5b54.png">

#### Liquid Crystal Display (LCD) & 2 RGB LEDs:
* To display the mode of the sanitiser system and the level of sanitiser liquid leff
* Left Red Light: No Liq.
* Left Purple Light: Low Liq.
* Left No Light: Sufficient Liq.
* Right Blue Light: Manual Mode
* Right Green: Automatic Mode.

<img width="129" alt="image" src="https://user-images.githubusercontent.com/122852792/229263883-09edbcd9-265d-4588-925a-4c4df48553f4.png"> <img width="139" alt="image" src="https://user-images.githubusercontent.com/122852792/229263895-e254bd0f-59d5-4711-b34e-78e7ffe0d141.png"> <img width="128" alt="image" src="https://user-images.githubusercontent.com/122852792/229263905-b252bf03-a8d7-4b67-a710-c4e246a60f0a.png">

#### 2 Ultrasonic Sensors:
* Detect level of santiser liquid
* Trigger the sanitiser system to spray during manual mode

#### 360 High Torque Servo Motor:
* Interface with the rack and pinion mechanism to exert force onto the spray heads
<img width="203" alt="image" src="https://user-images.githubusercontent.com/122852792/229263988-69a30eb5-96ea-4ed5-afa0-a431a98cb7e3.png">
