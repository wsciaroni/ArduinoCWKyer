#include "MorseOutput.h"

#include "morseChars.h"

void MorseOutput::sendStringAsCode(String &inputString)
{
    for(uint8_t i = 0; i < inputString.length(); i++)
    {
        sendMorseChar(inputString[i]);
    }
    Serial.println();
}

String MorseOutput::getUserInput()
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


/**
  Either send a space or the character
*/
void MorseOutput::sendMorseChar(const char& letter)
{
  // Serial.print("In sendMorseChar: ");
  Serial.print(letter);
  if(letter == ' ')
  {
    delay(CW_SPACE_UNIT_LEN_MILLISECONDS);//there is a seven unit delay between words
  }
  else 
  {
    byte bp = getMorseByte(letter);
    sendDawsAndDitsForChar(bp);
  }
}


char MorseOutput::getMorseByte(const char& letter)
{
  return morse_table[getCharIndex(letter)];
}


unsigned int MorseOutput::getCharIndex(const char& letter)
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

void MorseOutput::sendDawsAndDitsForChar(char bp) {
  bool isFirstFound = false;
  bool isDaw = 0;

  // for each bit in the byte,
  for (unsigned int i = 0; i < 8; i++, shiftLeftOne(bp))
  {
    bool isDaw = isFirstBitOne(bp);
    if (!isFirstFound)
    {
      if (isDaw)
      {
        isFirstFound = true;
      }
      else
      {
        // Keep going until a set bit is found
      }
    }
    // if we've seen our start flag then send the dash or dot based on the bit
    else if (isDaw)
    {
      sendDaw();
      //we have a one unit delay between parts of the letter
      delay(CW_UNIT_LEN_MILLISECONDS);
    }
    else
    {
      sendDit();
      //we have a one unit delay between parts of the letter
      delay(CW_UNIT_LEN_MILLISECONDS);
    }
  }

  // After the last dit or daw in the char, we've added one unit of space. Add two more here
  delay(CW_PARTIAL_SPACE_BETWEEN_CHARS);
}

bool MorseOutput::isFirstBitOne(const char& bp)
{
  return (bp & 0b10000000) != 0;
}

void MorseOutput::shiftLeftOne(char& bp)
{
  bp = bp << 1;
}

void MorseOutput::sendDit()
{
  // Serial.println("Sending Dot");
  outputHighForDuration(CW_UNIT_LEN_MILLISECONDS);
}

void MorseOutput::MorseOutput::sendDaw()
{
  // Serial.println("Sending Dash");
  outputHighForDuration(CW_DAW_UNIT_LEN_MILLISECONDS);
}

void MorseOutput::outputHighForDuration(int duration)
{
  digitalWrite(outputPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(duration);// wait for the set duration
  digitalWrite(outputPin, LOW);    // turn the LED off by making the voltage LOW
}
