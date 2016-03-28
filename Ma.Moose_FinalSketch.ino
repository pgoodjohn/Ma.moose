/*
 ___  _____     Ma.Moose musical gloves - Final Sketch.
|    |_   _|    This sketch is supposed to be run on a Bare Conductive touchboard.
|   _  | |      The project idea was of a glove that plays a sound everytime it touches something.
|___|  | |
      /_ /      Pietro Goodjohn Bongiovanni - June 2015
*/

/*
Notes on the sd should be named as follow in order for this code to run properly
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
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <SPI.h>
#include <Wire.h>

#define MPR121_ADDR 0x5C
#define MPR121_INT 4
#define SIZE 11

//Playtrack represents which note is being played by the board.
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
//Declarations for the two potentiometers.
int pot1 = 0;
int pot2 = 0;

//Initialization of SD Reader and MP3 Player
SdFat sd;
SFEMP3Shield player;

void setup() {
  Serial.begin(9600);

  //Check for the touch listener
  if (!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  //Check for the SD Reader
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }

  //Initialization of the MP3 Player
  player.begin();
  player.setVolume(0, 0);

  //Setting the threshold of the capacitive buttons
  MPR121.setTouchThreshold(8);
  MPR121.setReleaseThreshold(5);

  //Defining the two potentiometers in pin Input0 and Input1
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  //Reading the values of the potentiometers and mapping them accordingly
  pot1 = map(analogRead(A0), 0, 1023, 0, 11);
  pot2 = map(analogRead(A1), 0, 1023, 1, 4);

  Serial.println(pot1, pot2);

  //Pot1 is used to define the first note of the scale
  //Pot2 is used to decide which scale to build on top of the note chosen by Pot1
  track0 = pot1;

  if (pot2 == 1) {
    //Major Armonic Scale
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
    //Minor Armonic Scale
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
    //Major Penthatonic Scale
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
    //Minor Penthatonic Scale
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

  //Touch listener controls
  if (MPR121.touchStatusChanged())
  {
    MPR121.updateTouchData();
    if (MPR121.isNewTouch(0))
    {
      if (MPR121.isNewTouch(1))
      {
        //Updating the playtrack variable with the new note to be played
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
      //Stopping whatever notes was playing
      player.stopTrack();
      //Retriggering MP3 Player with new note
      player.playTrack(playtrack);
      //Printing which note is being played on the console
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
