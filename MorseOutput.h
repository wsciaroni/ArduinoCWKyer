#pragma once

#include <Arduino.h>

class MorseOutput
{
private:
    const int DOT_BLNK_LEN = 100;//Length of a dot is one unit
    const int DASH_BLNK_LEN = DOT_BLNK_LEN*3;//Length of a dash is three units

    uint8_t outputPin = 13;

    void sendDot();
    void sendDash();

    void blinkDelay(int duration);

    bool isFirstBitOne(const char& bp);
    void shiftLeftOne(char& bp);
    void sendDawsAndDitsForChar(char bp);
    unsigned int getCharIndex(const char& letter);
    char getMorseByte(const char& letter);
    void sendMorseChar(const char& letter);

public:
    MorseOutput(/* args */) {
        pinMode(outputPin, OUTPUT);
    }

    ~MorseOutput() = default;

    void sendStringAsCode(String& inputString);
};
