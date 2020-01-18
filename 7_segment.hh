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

#define SEGMENTS 7

/* Comment this out if display is common cathode */
#define COMMON_ANODE 

const uint8_t DIGITS[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 
                            0x5B, 0x5F, 0x70, 0xFF, 0x7B};
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
        
        if(num < 10)
        {
            digit = DIGITS[num];
        }

        digitalWrite(this->latch, LOW);

        for(uint8_t segment = 0; segment < SEGMENTS; ++segment)
        {
            digitalWrite(this->clk, LOW);
            
            #ifdef COMMON_ANODE
            if(digit & (0x01 << segment))
            {
                digitalWrite(this->data, LOW);        
            }
            else                  
            {
                digitalWrite(this->data, HIGH);     
            }
            
            #else
            if(digit & (0x01 << segment))
            {
                digitalWrite(this->data, HIGH);        
            }
            else                  
            {
                digitalWrite(this->data, LOW);     
            }                        
            #endif
            
            digitalWrite(this->clk, HIGH);
        } 
        digitalWrite(this->latch, HIGH);     
    }
    
  private:
    uint8_t data;
    uint8_t clk;
    uint8_t latch;

};

#endif /* 7_SEGMENT_H */
