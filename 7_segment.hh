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

#define SEGMENTS     7
#define NUM_DIGITS   10
#define NUM_LETTERS  20
/* 
 *  Lower case letters are offset from upper case in ascii table by  
 *  32 so this is used for converting case
*/
#define ASCII_OFFSET 32

static const uint8_t DIGITS[NUM_DIGITS] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 
                                           0x5B, 0x5F, 0x70, 0xFF, 0x7B};
                            
                                           /* A     b     C     d     E     F */ 
static const uint8_t LETTERS[NUM_LETTERS] = {0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47,
                                           /* G     H     i     J     L     n */
                                             0x5E, 0x37, 0x06, 0x3C, 0x0E, 0x15,
                                           /* o     p     q     r     S     t */
                                             0x1D, 0x67, 0x73, 0x05, 0x5B, 0x0F,
                                           /* U     y  */
                                             0x1C, 0x3B};          
                                            
/* Alphabet for getting letters - upper case */
static const char ALPHABET[NUM_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                                           'I', 'J', 'L', 'N', 'O', 'P', 'Q', 'R', 
                                           'S', 'T', 'U', 'Y'};

class SevenSegment
{
  public:
    SevenSegment(uint8_t data, uint8_t clk, uint8_t latch)
    {
        this->data = data;
        this->clk = clk;
        this->latch = latch;
        
        pinMode(this->data, OUTPUT);    
        pinMode(this->clk, OUTPUT);   
        pinMode(this->latch, OUTPUT);   
    }
    
    void set_num(uint8_t num)
    {
        uint8_t digit = 0;
        
        if(num < NUM_DIGITS)
        {
            digit = DIGITS[num];
        }
        write_to_disp(digit);
    }

    void set_letter(char letter)
    {
      write_to_disp(LETTERS[get_letter(letter)]);
    }
  
  private:
    uint8_t data;
    uint8_t clk;
    uint8_t latch;

    void write_to_disp(uint8_t character)
    {
        digitalWrite(this->latch, LOW);

        for(uint8_t segment = 0; segment < SEGMENTS; ++segment)
        {
            digitalWrite(this->clk, LOW);
            
            if(character & (0x01 << segment))
            {
                digitalWrite(this->data, LOW);        
            }
            else                  
            {
                digitalWrite(this->data, HIGH);     
            }
            
            digitalWrite(this->clk, HIGH);
        } 
        digitalWrite(this->latch, HIGH);      
    }

    /* Get index of letter in ALPHABET to get display pattern in LETTERS */
    uint8_t get_letter(char letter)
    {
        uint8_t letter_index = 0;
        
        for(uint8_t let = 0; let < NUM_LETTERS; ++let)
        {
            if(is_upper(letter))
            {
                if(ALPHABET[let] == letter)
                {
                   letter_index = let;
                }
            }
            else
            {
                if(ALPHABET[let] == lower_to_upper(letter))
                {
                   letter_index = let;
                }            
            }
        }
        return letter_index;       
    }

    /* Max upper case letter in ascii table is Z at 90 */
    bool is_upper(char let)
    {
        return (let < 91) ? true : false;
    }

    char lower_to_upper(char lower)
    {
        return lower - ASCII_OFFSET;  
    }
};


#endif /* 7_SEGMENT_H */
