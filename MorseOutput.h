#pragma once

#include <Arduino.h>

/// @brief Class that is used to generate CW Pulses of a word on a pin
class MorseOutput
{
private:
    /**
     * @brief Length of 1 unit of CW in Milliseconds
     * 
     * Based on the word Paris:
     * | WPM | MILL |
     * | --- | ---- |
     * |   1 | 1200 |
     * |   5 |  240 |
     * |  10 |  120 |
     * |  15 |   80 |
     * |  20 |   60 |
     * |  25 |   48 |
     * |  30 |   40 |
     * |  40 |   30 |
     */
    const int CW_UNIT_LEN_MILLISECONDS = 80;                                // Length of a dot is one unit
    const int CW_DASH_UNIT_LEN_MILLISECONDS = CW_UNIT_LEN_MILLISECONDS*3;   // Lenght of a dash is 3 units
    const int CW_SPACE_UNIT_LEN_MILLISECONDS = CW_UNIT_LEN_MILLISECONDS*7;  // Length between words is 7 units

    uint8_t outputPin;

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
    MorseOutput(uint8_t pin) : outputPin(pin) {
        pinMode(outputPin, OUTPUT);
    }

    ~MorseOutput() = default;

    void sendStringAsCode(String& inputString);

    String getUserInput();
};
