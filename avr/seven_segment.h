/*
    7 segment display driver using 74hc595 shift register

    n abcdefg
    0 1111110
    1 0110000
    2 1101101
    3 1111001
    4 0110011
    5 1011011 
    6 1011111
    7 1110000
    8 1111111
    9 1111011
*/

#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>
#include "gpio.h"

#define SEGMENTS    7
#define NUM_DIGITS  10
#define NUM_LETTERS 20

namespace z_lib{


/* 
 *  Lower case letters are offset in ascii table by  
 *  65 so this is used for finding letter
*/
#define ASCII_OFFSET 65

static const uint8_t DIGITS[NUM_DIGITS] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 
                                           0x5B, 0x5F, 0x70, 0xFF, 0x7B};
                            
                                /* A     b     C     d     E     F */ 
static const uint8_t LETTERS[] = {0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47,
                                /* G     H     i     J     L     n */
                                  0x5E, 0x37, 0x06, 0x3C, 0x0E, 0x15,
                                /* o     p     q     r     S     t */
                                  0x1D, 0x67, 0x73, 0x05, 0x5B, 0x0F,
                                /* U     y  */
                                  0x1C, 0x3B};          
                                            
/* Alphabet for getting letters - upper case */
static const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                                'I', 'J', 'L', 'N', 'O', 'P', 'Q', 'R', 
                                'S', 'T', 'U', 'Y'};

class SevenSegment
{
  public:
    SevenSegment(Gpio data, Gpio clk, Gpio latch);
    void set_num(uint8_t num);
    void set_letter(char letter);

  private:
    Gpio *data;
    Gpio *clk;
    Gpio *latch;

    uint8_t get_letter(char letter);
};

}

#endif /* 7_SEGMENT_H */
