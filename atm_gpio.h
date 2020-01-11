#ifndef ATM_GPIO_H
#define ATM_GPIO_H

enum class Mode
{
    INPUT = 0,
    OUTPUT
};

enum class Port
{
    B = 0,
    C, 
    D
};

class Gpio
{
    public:
        Gpio(Port port, uint8_t pin, Mode mode)
        {
            this->port = port;
            this->pin  = pin;
            
            if(mode == Mode::OUTPUT)
            {
                switch(port)
                {
                    case(Port::B):
                        DDRB |= (0x01 << pin);
                        break;
                        
                    case(Port::C):
                        DDRC |= (0x01 << pin);
                        break;
                        
                    case(Port::D):
                        DDRB |= (0x01 << pin);
                        break;                        
                }                
            }
        }
        
        void set(void)
        {
            switch(this->port)
            {
                case(Port::B):
                    PORTB |= (0x01 << this->pin);
                    break;

                case(Port::C):
                    PORTC |= (0x01 << this->pin);
                    break;

                case(Port::D):
                    PORTD |= (0x01 << this->pin);
                    break;                        
            }                                
        }
        
        void clear(void)
        {
            switch(this->port)
            {
                case(Port::B):
                    PORTB &= ~(0x01 << this->pin);
                    break;

                case(Port::C):
                    PORTC &= ~(0x01 << this->pin);
                    break;

                case(Port::D):
                    PORTD &= ~(0x01 << this->pin);
                    break;                        
            }           
        }
 
        void toggle(void)
        {
            switch(this->port)
            {
                case(Port::B):
                    PORTB ^= (0x01 << this->pin);
                    break;

                case(Port::C):
                    PORTC ^= (0x01 << this->pin);
                    break;

                case(Port::D):
                    PORTD ^= (0x01 << this->pin);
                    break;                        
            }           
        }    
    
        bool read()
        {
            bool ret_val = false;
            
            switch(this->port)
            {
                case(Port::B):
                    PINB &= ~(0x01 << this->pin);
                    ret_val = true;

                case(Port::C):
                    PINC &= ~(0x01 << this->pin);
                    ret_val = true;

                case(Port::D):
                    PIND &= ~(0x01 << this->pin);           
                    ret_val = true;
            }           
            return ret_val;
        }
        
    private:
        uint8_t port;
        uint8_t pin;
        Mode mode;

};



#endif /* ATM_GPIO_H */
