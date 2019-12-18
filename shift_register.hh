#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

enum class Mode
{
    BAR = 0,
    POINT    
};

class ShiftReg
{
    public:
        ShiftReg(uint8_t d_pin, uint8_t l_pin, uint8_t c_pin, Mode m)
        {
            this->data_pin  = d_pin;
            this->latch_pin = l_pin;
            this->clock_pin = c_pin;
            this->mode      = m;

            pinMode(d_pin, OUTPUT);
            pinMode(l_pin, OUTPUT);
            pinMode(c_pin, OUTPUT);
        }

        void set_mode(Mode mode)
        {
            this->mode = mode;    
        }
        
        void set_value(uint8_t display_val)
        {
            uint8_t register_val = 0x00;
            register_val = BAR_MAP[display_val];
            digitalWrite(latch_pin, LOW);
        
            for(int led = 0; led < 8; led++)
            {
                digitalWrite(clock_pin, LOW);
                if(this->mode == Mode::BAR)
                {
                    if(register_val & (0x01 << led))                  
                        digitalWrite(data_pin, HIGH);                    
                    else                  
                        digitalWrite(data_pin, LOW);     
                }
                else if(this->mode == Mode::POINT)
                {
                    if((0x01 << display_val) & (0x01 << led))                   
                        digitalWrite(data_pin, HIGH);                    
                    else                   
                        digitalWrite(data_pin, LOW); 
                        
                }
                digitalWrite(clock_pin, HIGH);
            } 
            digitalWrite(latch_pin, HIGH);
        }

        void fade_up(void)
        {
            for(int i = 0; i < 8; i++){
                this->set_value(i);
                delay(200);    
            }
        }

        void fade_down(void)
        {
            for(int i = 8; i > 0; i--){
                this->set_value(i);
                delay(200);    
            }               
        }
        
    private:
        uint8_t data_pin;
        uint8_t latch_pin;
        uint8_t clock_pin;    

        Mode mode;

        const uint16_t BAR_MAP[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
};

#endif /*SHIFT_REGISTER_H*/
