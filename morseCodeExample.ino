#include "MorseOutput.h"

String getInput();

MorseOutput m;

void setup() {
  Serial.begin(115200); // open the serial port at 9600 bps:
  // initialize digital pin 13 as an output. (Same pin used in Blink)
}

// the loop function runs over and over again forever
//It will move from each letter in the 'message' variable 
void loop() 
{ 
  String inputString = getInput();
  m.sendStringAsCode(inputString);
  Serial.println();
}

String getInput()
{
  // Prompt the user for input
  Serial.println("Enter message:");

  //wait for data available
  while (Serial.available() == 0) {}

  // Read the string
  String inputString = Serial.readString();

  // Trim whitespace
  inputString.trim();

  // Make uppercase string
  inputString.toUpperCase();
  
  // Echo out the string to the terminal
  // Serial.println(inputString);
  
  // Return the string that we received
  return inputString;
}