grantareprap
============

Configuration, 3D models and tutorials for the prusa mendel i3 we built at the office

Folder structure:

*firmware

Tweaked version of the customized firmware by Marlin. We had to change some values in configuration.h to invert behaviour in some axis.

*Other software

Links and zip files to the rest of the software stack (printrun, slic3r, cad packages)

*3D models

.stl files for printing

How to configure a host for the printer
=======================================

Install all programs in \OtherSoftware

Open \firmware\firmware\it3 minitronics\Marlin-Marlin_v1\Marlin\Marlin.ino in arduino IDE

Connect your computer to the minitronics board in the printer with a USB cable.

Check that LED lights in the minitronics board in the printer light.

Check that all axis of the printer are free to move, the tray is clean of printed parts.

Plug the printer to a power outlet and switch on.

Check that LED lights in printer power supply are on.

Click 'File' -> 'Upload' in Arduino IDE to transfer firmware to printer.

Now the printer is ready to work.

Open \OtherSoftware\Printrun-Win-Slic3r-12July2013\pronterface.exe

Check all printing parameters correspond to the type of plastic (ABS, PLA) used.

Load the .stl or .gcode file for the model to print.

Hit 'print' button.
