## leAFS (leading edge air filtering system)
leAFS is an automatic 360 table sanitiser incorporated with an air purifier. It is designed to be situated in schools and offices.

The software of leAFS is build using Arduino Uno and basic C++ language using Arduino IDE platform. The system consists of 2 parts: the sanitiser (middle portion) and the air purifier (bottom portion).

<img width="185" alt="image" src="https://user-images.githubusercontent.com/122852792/229262506-194347ba-0049-42d4-8c8d-479e5e175316.png"> 
[Full Video](https://user-images.githubusercontent.com/122852792/229262905-abc1ff73-0e79-40f0-9151-3a1ef38733d6.mp4)

### Mechatronic Components used:
* 2 Arduino UNO R3
* 1 12V 5A Power Supply
* 2 Step down buck converters
* Resistors (330 ohms & 10k ohms)
* 1 Potentiometer
* 12V 2A Fan
* 1 Piezo Buzzer
* 2 Latching Pushbutton
* 1 Liquid Crystal Display (LCD) & 2 RGB LEDs
* 2 Ultrasonic Sensors:
* 1 360 High Torque Servo Motor

Refer to [functions.md](https://github.com/YapZhenYan/MA2079-Engineering-Innovation-and-Design/blob/main/functions.md) for more details on the functions for each of the components and the [circuit diagram](https://github.com/YapZhenYan/MA2079-Engineering-Innovation-and-Design/blob/main/leAFS%20Schematic%20Diagram.pdf) for the connection of the components.

### Some improvements to consider:
* Scale down the size of leAFS
* Build a PCB board instead and use esp32
* Build a stronger sanitiser system (add more motors, change the structure)
* Include a purification detection system to determine how much air is undergoing purification from the HEPA Filter
* Enable the sanitiser system to sanitise at different range catering to different table size
