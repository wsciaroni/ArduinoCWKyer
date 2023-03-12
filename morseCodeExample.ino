#include "MorseOutput.h"

MorseOutput m(13);

void setup()
{
  Serial.begin(115200); // open the serial port at 9600 bps:
  // initialize digital pin 13 as an output. (Same pin used in Blink)
}

// the loop function runs over and over again forever
// It will move from each letter in the 'message' variable
void loop()
{
  String inputString = m.getUserInput();
  if (m.isChangeSpeedCommand(inputString))
  {
    m.handleCwChangeSpeedCommand(inputString);
  }
  else
  {
    m.sendStringAsCode(inputString);
  }
}
