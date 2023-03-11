/*

  Has the ability to output

*/

#include "morseChars.h"

String message;
char currSignal = '\0';
int currMsgIdx = 0;
uint8_t ledPin = 13;

void blinkDelay(int duration)
{
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(duration);// wait for the set duration
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
}

void sendDot()
{
  // Serial.println("Sending Dot");
  blinkDelay(DOT_BLNK_LEN);
}

void sendDash()
{
  // Serial.println("Sending Dash");
  blinkDelay(DASH_BLNK_LEN);
}

void sendDawsAndDitsForChar(byte bp) {
  bool isFirstFound = false;
  byte ditordah = 0;

  // for each bit in the byte,
  for (unsigned int i = 0; i < 8; i++, bp = (bp << 1))
  {
    // Serial.print(i);
    // Serial.print(": ");
    ditordah = (bp & 0b10000000); // Get the first bit of the sequence
    // Serial.println(ditordah);
    // if havent
    if (!isFirstFound)
    {
      if (ditordah != 0)
      {
        isFirstFound = true;
      }
      else
      {
        // Keep going until a set bit is found
      }
    }
    // if we've seen our start flag then send the dash or dot based on the bit
    else if (ditordah == 0)
    {
      sendDot();
      //we have a one unit delay between parts of the letter
      delay(DOT_BLNK_LEN);
    }
    else
    {
      sendDash();
      //we have a one unit delay between parts of the letter
      delay(DOT_BLNK_LEN);
    }
  }

  // there is a three element delay between chacaters.  the sendDash() or
  // sendDot() functions already add a one element delay so we delay
  // two more element times.
  delay(DOT_BLNK_LEN * 2);
}

unsigned int getCharIndex(const char& letter)
{
  static const unsigned int UPPER_LETTER_OFFSET = 'A' - 10;
  static const unsigned int LOWER_LETTER_OFFSET = 'a' - 10;
  static const unsigned int NUMBER_OFFSET = '0';
  if(letter >= 'A' && letter <= 'Z') {
    return letter - UPPER_LETTER_OFFSET;
  }
  else if(letter >= 'a' && letter <= 'z')
  {
    return letter - LOWER_LETTER_OFFSET;
  }
  else if(letter >= '0' && letter <= '9')
  {
    return letter - NUMBER_OFFSET;
  }
  else if(letter == '#')
  {
    return 36;
  }
  else if(letter == '+')
  {
    return 37;
  }
  else if(letter == ',')
  {
    return 38;
  }
  else if(letter == '-')
  {
    return 39;
  }
  else if(letter == '.')
  {
    return 40;
  }
  else if(letter == '/')
  {
    return 41;
  }
  else if(letter == '=')
  {
    return 42;
  }
  else if(letter == '?')
  {
    return 43;
  }
  else if(letter == '^')
  {
    return 44;
  }
}

byte getMorseByte(const char& letter)
{
  return morse_table[getCharIndex(letter)];
}

void sendMorseChar(const char& letter)
{
  // Serial.print("In sendMorseChar");
  // Serial.println(letter);
  if(letter == ' ')
  {
    delay(DOT_BLNK_LEN * 7);//there is a seven unit delay between words
  }
  else 
  {
    byte bp = getMorseByte(letter);
    sendDawsAndDitsForChar(bp);
  }
}

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  // initialize digital pin 13 as an output. (Same pin used in Blink)
  pinMode(ledPin, OUTPUT);

  message = "CQ cq CQ DE W1AZZ";
}

// the loop function runs over and over again forever
//It will move from each letter in the 'message' variable 
void loop() 
{ 
  Serial.println("Enter message:");
  while (Serial.available() == 0) {}     //wait for data available
  String inputString = Serial.readString();  //read until timeout
  inputString.trim();  
  for(int i = 0; i < inputString.length(); i++) {
    sendMorseChar(inputString[i]);
  }
}