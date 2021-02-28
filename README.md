# Logitech G25 wheel to PPM
Instead of just using your old G25 to play games, now you can pair it with an arduino usb shield and transmitter to use it to drive any RC car. This is not well tested software, so use at your own risk. Please use your common sense and do not use this in a way that can potentially cause injuries to others. 

![alt text](https://github.com/lexfp/G25toPPM/blob/master/overview.jpg?raw=true)

https://youtu.be/leFdxP0LLkY  
 
## License
This code is in part based on the examples found in https://github.com/felis/USB_Host_Shield_2.0 and is thus released under the same GNU General Public License.

## Requirements
Logitech G25 steering wheel along with pedals (shifter is supported, but not required)
Arduino Uno (or equivalent clone)
Arduino USB Shield
PPM Driven TX module (see below)

## Installation
Search for tutorials for on up Arduino so you can at least download sketches and upload them to your arduino. You will also need to be able to install arduino libraries such as the usb host shield library here:   
https://github.com/felis/USB_Host_Shield_2.0/archive/master.zip  
I will not cover any of these steps as they are covered in depth in many other places if you search for it.
The only two things I will cover are for cheap cloned boards from China. The clones will often use a different driver (CH340). Lots of sites will cover how to install this.  
The clone usb shields may need some additional jumpers bridged or they will not work.   
See https://esp8266-notes.blogspot.com/2017/08/defective-arduino-usb-host-shield-boards.html  
Contrary to the article, these boards are not defective, but rather they just don't come fully configured and ready to go from the factory. Welcome to the hobby!

## Wiring
See wiring.jpg image in codebase.  
With the module lights and dials facing you and the antenna facing up, you will find 5 pins on the bottom right. The top pin on the module will go to pin 3 on your arduino board (you can change that in the code). Pins 3 on the module is for your battery + and pin 4 is ground. I wired them directly to my arduino battery terminal so that everything is powered once I power on the arduino. I believe that they can both take 3s although I've opted to use 2s. You can disregard the other pins.

## Configuration
The only things that are being used by default are the gas & break pedal along with the steering wheel and shifter. The break pedal works similar to pushing up on the throttle in pistol style transmitter (as both a break and reverse). The gas and break both map to the throttle channel similar to a real transmitter. The values you will most likely need to modify in the code are (in BtnPPMMap.h):  

NUM_CHANNELS - number of channels on your RX.   
The code can also accept input from the shifter (only up and downshift though, not the gears), but doesn't use that functionality at the moment.  

WHEEL_LEFT/RIGHT_TURN_LIMIT - On some cars, the servos can turn further than the wheels can, which can cause them to wear out faster. You can adjust these values here. Values are actual PPM values being sent to the receiver (1000-2000).

WHEEL_CENTER - this is for trimming the center of your steering. Values are PPM values with 1500 being the default.

PPM_THROTTLE_NEUTRAL - this is the value of the neutral point for your ESC. You can recalibrate using the pedals, of course and leave it close to either 1500 or 1300 depending on your transmitter.     

GEAR_FORWARD & REVERSE_LIMITs - the gears are used as a sort of throttle limit. Each gear will limit the max throttle to the desired range. If you don't have a shifter, just set the FIRST_GEAR_LIMIT value to the desired throttle cap you wish to use (100 if you don't want a cap). The value is in percentages. 5 would be 5%, 10 is 10%, 100 is 100% etc... When in first gear, then the limits for first gear would apply for both throttle and reverse. You do not have to shift to first gear before going into reverse since the break always works as a reverse pedal as well.

## Transmitter Modules
The modules linked below should work, but in general, if you can operate the module in opentx with PPM mode, it should work. I tested with the module in the first link and also the crossfire module.  

https://www.team-blacksheep.com/products/prod:crossfire_micro_tx  

https://www.banggood.com/2_4G-CC2500-NRF24L01-A7105-CTRF6936-4-IN-1-Multi-protocol-STM32-TX-Module-With-Antenna-p-1153902.html?p=Y506095296511201607R&custlinkid=1443521  

https://www.banggood.com/IRangeX-IRX4-Plus-2_4G-CC2500-NRF24L01-A7105-CYRF6936-4-IN-1-Multiprotocol-STM32-TX-Module-With-Case-p-1225080.html?p=Y506095296511201607R&custlinkid=1443522  

## Inspired by
Code is, however, based off of the t16km example in the shield library and the ppm encoder code by David Hasko.  
https://github.com/felis/USB_Host_Shield_2.0/tree/master/examples/HID/t16km  
https://github.com/DzikuVx/ppm_encoder  
