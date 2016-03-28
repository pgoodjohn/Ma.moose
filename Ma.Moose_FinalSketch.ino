/*
 ___  _____     Ma.Moose musical gloves - Final Sketch.
|    |_   _|    This sketch is supposed to be run on a Bare Conductive touchboard.
|   _  | |      The project idea was of a glove that plays a sound everytime it touches something.
|___|  | |
      /_ /      Pietro Goodjohn Bongiovanni - June 2015
*/

/*
Notes on the sd should be named as follow in order for this baseline code to run properly
TRACK 000 = DO
TRACK 001 = DO#
TRACK 002 = RE
TRACK 003 = RE#
TRACK 004 = MI
TRACK 005 = FA
TRACK 006 = FA#
TRACK 007 = SOL
TRACK 008 = SOL#
TRACK 009 = LA
TRACK 010 = LA#
TRACK 011 = SI
*/

#include <MPR121.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

#define MPR121_ADDR 0x5C
#define MPR121_INT 4
#define SIZE 11

//playtrack is the variable in which is stored the value of the track being played, it gets updated every time
//a new pin is touched, when the touchboard is fired up there is no value stored in this variable
//it gets a value as soon as one pin (or one finger of the glove is pressed)
int playtrack;

//I tried making it work with some arrays but the TouchBoard wasn't too happy about it and refused to work
//Had to go back to single variables, not the best thing, but it works.
int track0;
int track1;
int track2;
int track3;
int track4;
int track5;
int track6;
int track7;
int track8;
int track9;
int track10;
int track11;
//declaration for the two potentiometers, the actual values are defined some lines below, mapped and stuff
int pot1 = 0;
int pot2 = 0;

//initializing sd reader and mp3 player
SdFat sd;
SFEMP3Shield player;

void setup() {
  Serial.begin(9600);

  //checking if mp3 player is working
  if (!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  //checking if sd is working correctly
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }

  //initializing mp3 player
  player.begin();
  player.setVolume(0, 0);

  //threshold of touch
  MPR121.setTouchThreshold(8);
  MPR121.setReleaseThreshold(5);

  //defining the inputs for the potentiometers, standard stuff for this arduino stuff
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  //read and map potentiometer for scales
  pot1 = map(analogRead(A0), 0, 1023, 0, 11);
  pot2 = map(analogRead(A1), 0, 1023, 1, 4);

  Serial.println(pot1, pot2);

  //Pot1 defines the first note of the tracks so that pot2 can build the scales with algorithms
  //pot1 is mapped above to return values from 0 to 11 which correspond to the notes saved on the micro sd
  //card, by deciding the first note of the scale with a potentiometer we can use a second one to build on this
  //one scales by simply adding values to select other samples, which is done by the switch based on pot2
  track0 = pot1;

  //switch for pot 2, deciding the type of scale which is built on the first note defined by pot 1
  if (pot2 == 1) {
    //major armonic
    track1 = track0 + 2;
    track2 = track0 + 4;
    track3 = track0 + 5;
    track4 = track0 + 7;
    track5 = track0 + 9;
    track6 = track0 + 11;
    track7 = track0 + 14;
    track8 = track0 + 16;
    track9 = track0 + 17;
    track10 = track0 + 19;
    track11 = track0 + 23;
    Serial.println("Maj");
  }
  if (pot2 == 2) {
    //minor armonic
    track1 = track0 + 1;
    track2 = track0 + 2;
    track3 = track0 + 4;
    track4 = track0 + 5;
    track5 = track0 + 7;
    track6 = track0 + 8;
    track7 = track0 + 11;
    track8 = track0 + 12;
    track9 = track0 + 14;
    track10 = track0 + 15;
    track11 = track0 + 18;
    Serial.println("min");
  }
  if (pot2 == 3) {
    //major pentatonic (1, 2, 3, 5, 6tones)
    track1 = track0 + 2;
    track2 = track0 + 3;
    track3 = track0 + 5;
    track4 = track0 + 7;
    track5 = track0 + 8;
    track6 = track0 + 10;
    track7 = track0 + 14;
    track8 = track0 + 15;
    track9 = track0 + 19;
    track10 = track0 + 20;
    track11 = track0 + 22;
    Serial.println("Penthatonic Maj");
  }
  if (pot2 == 4) {
    //minor pentatonic (1, 3, 4, 5, 7 tones)
    track1 = track0 + 2;
    track2 = track0 + 3;
    track3 = track0 + 4;
    track4 = track0 + 6;
    track5 = track0 + 7;
    track6 = track0 + 9;
    track7 = track0 + 10;
    track8 = track0 + 13;
    track9 = track0 + 14;
    track10 = track0 + 16;
    track11 = track0 + 17;
    Serial.println("Penthatonic Min");
  }

  //this serie of function of MPR121 allows us to operate with the capacitive pins on the touchboard
  //the first condition triggers when any of the pin is touched and triggers the whole cycle
  if (MPR121.touchStatusChanged())
  {
    //this second function returns the number of the pin touched so that the function can go to the correct
    //part of the cycle and reproduce the corresponding sound
    MPR121.updateTouchData();
    if (MPR121.isNewTouch(0))
    {
      //all these nested ifs are needed to check if two pins are pressed at the same moment...
      //i still need to think about this, there is probably a better way to implement all this code.
      if (MPR121.isNewTouch(1))
      {
        playtrack = track5;
      }
      else if (MPR121.isNewTouch(2))
      {
        playtrack = track6;
      }
      else if (MPR121.isNewTouch(3))
      {
        playtrack = track7;
      }
      else
      {
        playtrack = track0;
      }
      //this line of code stops the sample that was previously playing so that a new sample can start as soon
      //as i click one of the buttons on my glove
      player.stopTrack();
      //this line triggers the sample which starts playing immediatly
      player.playTrack(playtrack);
      //this line is just for debugging, prints to the serial number the number of track which is being
      //played
      Serial.println(playtrack);
    }
    if (MPR121.isNewTouch(1))
    {
      if (MPR121.isNewTouch(0))
      {

      }
      else if (MPR121.isNewTouch(2))
      {
        playtrack = track8;
      }
      else if (MPR121.isNewTouch(3))
      {
        playtrack = track9;
      }
      else
      {
        playtrack = track1;
      }
      player.stopTrack();
      player.playTrack(playtrack);
      Serial.println(playtrack);
    }
    if (MPR121.isNewTouch(2))
    {
      if (MPR121.isNewTouch(1))
      {

      }
      else if (MPR121.isNewTouch(0))
      {

      }
      else if (MPR121.isNewTouch(3))
      {
        playtrack = track10;
      }
      else
      {
        playtrack = track2;
      }
      player.stopTrack();
      player.playTrack(playtrack);
      Serial.println(playtrack);
    }
    if (MPR121.isNewTouch(3))
    {
      if (MPR121.isNewTouch(1))
      {

      }
      else if (MPR121.isNewTouch(2))
      {

      }
      else if (MPR121.isNewTouch(0))
      {

      }
      else
      {
        playtrack = track3;
      }
      player.stopTrack();
      player.playTrack(playtrack);
      Serial.println(playtrack);
    }
  }
}