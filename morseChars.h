const int DOT_BLNK_LEN = 100;//Length of a dot is one unit
const int DASH_BLNK_LEN = DOT_BLNK_LEN*3;//Length of a dash is three units

//Here the first 1 is a start flag and the reaminder of the byte indicates the sequence.
//For example A's sequence is 01 or dot-dash. 
//The preceeding zeroes are shifted out until the start flag is found which is also discarded.
const char morse_table[] = {
  0B00111111, // '0'
  0B00101111, // '1'
  0B00100111, // '2'
  0B00100011, // '3'
  0B00100001, // '4'
  0B00100000, // '5'
  0B00110000, // '6'
  0B00111000, // '7'
  0B00111100, // '8'
  0B00111110, // '9'

  0B00000101, // 'A' 10 Index = char - 'A' + 10
  0B00011000, // 'B' 11
  0B00011010, // 'C' 12
  0B00001100, // 'D' 13
  0B00000010, // 'E' 14
  0B00010010, // 'F' 15
  0B00001110, // 'G' 16
  0B00010000, // 'H' 17
  0B00000100, // 'I' 18
  0B00010111, // 'J' 19
  0B00001101, // 'K' 20
  0B00010100, // 'L' 21
  0B00000111, // 'M' 22
  0B00000110, // 'N' 23
  0B00001111, // 'O' 24
  0B00010110, // 'P' 25
  0B00011101, // 'Q' 26
  0B00001010, // 'R' 27
  0B00001000, // 'S' 28
  0B00000011, // 'T' 29
  0B00001001, // 'U' 30
  0B00010001, // 'V' 31
  0B00001011, // 'W' 32
  0B00011001, // 'X' 33
  0B00011011, // 'Y' 34
  0B00011100, // 'Z' 35

  0B11000101, // '#' 36 // /BK - Break in conversation
  0B00101010, // '+' 37 // /AR - Message separator, start new message / telegram
  0B01110011, // ',' 38
  0B01100001, // '-' 39
  0B01010101, // '.' 40
  0B00110010, // '/' 41
  0B00110001, // '=' 42 // BT - Start of new section / new paragraph
  0B01001100, // '?' 43 // Please say again
  0B01000101, // '^' 44 // /SK - End of contact / End of work
};