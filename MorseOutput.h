#pragma once

#include <Arduino.h>

/// @brief Class that is used to generate CW Pulses of a word on a pin
class MorseOutput
{
public:
    MorseOutput(uint8_t pin) : outputPin(pin) {
        pinMode(outputPin, OUTPUT);
    }

    ~MorseOutput() = default;

    void sendStringAsCode(String& inputString);
    String getUserInput();

protected:
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
    const int CW_UNIT_LEN_MILLISECONDS = 80;                                // Length of a dit is one unit
    const int CW_DAW_UNIT_LEN_MILLISECONDS = CW_UNIT_LEN_MILLISECONDS*3;    // Lenght of a daw is 3 units
    const int CW_SPACE_UNIT_LEN_MILLISECONDS = CW_UNIT_LEN_MILLISECONDS*7;  // Length between words is 7 units
    const int CW_PARTIAL_SPACE_BETWEEN_CHARS = CW_UNIT_LEN_MILLISECONDS*2;

    uint8_t outputPin;

    void sendMorseChar(const char& letter);
    char getMorseByte(const char& letter);
    unsigned int getCharIndex(const char& letter);

    void sendDawsAndDitsForChar(char bp);

    bool isFirstBitOne(const char& bp);
    void shiftLeftOne(char& bp);

    void sendDit();
    void sendDaw();

    void outputHighForDuration(int duration);
};
