# Ma.Moose Music Gloves
> Arduino Sketch to be loaded onto a Bare Conductive Touchboard for Ma.Moose Music Gloves.

With this sketch loaded onto your Touchboard, it will be able to play a single notes every time one or more of the first four capacitive touch button are touched. It only uses the first four buttons because the sketch is studied for one glove with a touch sensor placed on four fingers.
The sound it plays are samples which need to be saved onto the microSD card in the Touchboard, the files should be named from TRACK000.mp3 to TRACK011.mp3 and they can be, virtually, of every instrument you want.
The sketch also reads the status of two potentiometers (in pin 0 and 1): the first potentiometer is used to decide the first note of the scale so that the rest of it can be built by the board, the second potentiometer is used to decide which kind of scale needs to be generated. This script is able to generate, for the moment, Major, Minor, Penthatonic Major and Penthatonic Minor scales.
This sketch was built during the Arduino Disability Orchestra program organized during the Academic Year 2014/2015 by Politecnico di Torino.


## Installation

Open with the Arduino sketch editor and upload on your Bare Conductive Touchboard.
You can follow this [link](http://www.bareconductive.com/make/setting-up-arduino-with-your-touch-board/) in order to setup your Arduino environment in order to work perfectly with the Touchboard.


## Release History

* 1.0.1
    * CHANGE: Update docs and code comments (module code remains unchanged)

## Meta

Pietro Bongiovanni – [@pietrogoodjohn](https://twitter.com/pietrogoodjohn) – bongiovanni.pietro.vc@gmail.com

Distributed under the MIT license. See ``LICENSE`` for more information.

[https://github.com/pgoodjohn](https://github.com/pgoodjohn)
