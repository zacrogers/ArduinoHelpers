#include "seven_segment.h"

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



namespace z_lib
{
    SevenSegment::SevenSegment(Gpio *data, Gpio *clk, Gpio *latch)
    {
        this->data = data;
        this->clk = clk;
        this->latch = latch;
    }
    
    void SevenSegment::set_num(uint8_t num)
    {
        uint8_t digit = 0;
        
        if(num < NUM_DIGITS)
        {
            digit = DIGITS[num];
        }

        *this->latch.clear();

        for(uint8_t segment = 0; segment < SEGMENTS; segment++)
        {
            *this->clk.clear();
            
            if(digit & (0x01 << segment))
            {
                *this->data.clear();
            }
            else                  
            {
                *this->data.set();
            }
            *this->clk.set();
        } 
        *this->latch.set();
    }

    void SevenSegment::set_letter(char letter)
    {
      uint8_t curr_letter = LETTERS[get_letter(letter)];
      
        *this->latch.clear();

        for(uint8_t segment = 0; segment < SEGMENTS; segment++)
        {
            *this->latch.clear();
            
            if(curr_letter & (0x01 << segment))
            {
                *this->data.clear();
            }
            else                  
            {
                *this->data.set();
            }
            
            *this->clk.set();
        } 
        *this->latch.set();      
    }

    uint8_t SevenSegment::get_letter(char letter);
    {
      uint8_t letter_index   = 0;
      
      for(uint8_t let = 0; let < NUM_LETTERS; ++let)
      {
          /* Compare upper case */
          if(ALPHABET[let] == letter)
          {
             letter_index = let;
          }
          /* Compare lower case:*/
          else if(ALPHABET[let] == (letter + ASCII_OFFSET))
          {
            letter_index = let; 
          }             
      }
      return letter_index;       
    }
}
