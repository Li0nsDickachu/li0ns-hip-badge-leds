this arduino code makes a fun LED animation on the HiP Berlin badge.

these are the steps I follow to put this code on my badge. I don't know if they are all necessary but this is what worked for me:

*install arduino IDE 2.1.1
*follow this tutorial to add the ESP32 board manager to Arduino IDE https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html
*open the .ino file from this repository in Arduino IDE
*for "Select Board" I choose Adafruit QT Py ESP32-C3
*plug my badge into my computer using a USB-C cable
*switch the badge ON. note: the 3 colored on the bottom left do not indicate on/off status. instead, look at D17 or the silkscreen on the back to make sure it is on
*under "Tools" next to "Ports" select the port that shows up when you connect and turn on the badge. in my case this is /dev/ttyACM0
*click the upload button to upload the sketch to your badge


debug tips:
if the "Ports" menu is grayed out, it usually means the badge is off, or not connected properly.
if you want to check whether your computer recognizes your badge at all, open a terminal, and do:

cd /dev
ls

then check whether you see "ttyACM0" in the list. or unplug the badge and run the command again, and check whether any ports disappeared from the list.

