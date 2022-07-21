/*
    That a simple, fast and  memory efficient way 
    to cross the whole milky way of the dicovery board !
*/

//Physical registers for GPIO switch.
volatile uint32_t* ___GPIOE_MODER = (volatile uint32_t *) 0x48001000;
volatile uint32_t* ___GPIOA_MODER = (volatile uint32_t *) 0x48000000;
volatile uint32_t* ___GPIOA_PUPDR = (volatile uint32_t *) 0x4800000C;
volatile uint32_t* ___RCC_AHBENR = (volatile uint32_t *) 0x40021014;
volatile uint32_t* ___ODR = (volatile uint32_t *) 0x48001014;

//Physical register for interrupt basic config.
volatile uint32_t* ___EXIT_IMR1 = (volatile uint32_t*) 0x40010400;
volatile uint32_t* ___EXIT_RTSR1 = (volatile uint32_t*) 0x40010408;
volatile uint32_t* ___EXIT_FTSR1 = (volatile uint32_t *) 0x4001040C;
volatile uint32_t* ___SYSCFG_EXTI1CR1 = (volatile uint32_t *) 0x40010008;


void setup() {
  Serial.begin(9600);
  Serial.println("Program start");
  *___RCC_AHBENR |= 0x220000;        // Enable clock on port E and A  
  *___GPIOE_MODER = 0x55550000;      // Enable all leds on the demo wheel in output mode on GPIO_E.
  *___GPIOA_MODER &= ~0x3;           // Set PA0 (press button) as input on GPIO_A.

  *___GPIOA_PUPDR &= ~0x3;           //  Set PA0 in pull-up mode 
  *___GPIOA_PUPDR |= 0x1;            //  (lvl high when not pressed)
  //Serial.println(*___GPIOE_MODER, HEX);

  // setting up EXTI0 interrupt on PA0 easly from datasheet.
  *___EXIT_IMR1 |= 1;                 // Disable mask bit for EXTI0;
  *___EXIT_RTSR1 |= 1;                // Set interrupt in Raising trigger mode ON.
  *___EXIT_RTSF1 &= ~1;                // Set interrupt in Falling trigger mode OFF.
  *___SYSCFG_EXTI1CR1 &= ~0x7;        // Set PA0 on EXTI0 

  // Now i "just" need to handle the ISR by pointing a C function from the vector table
  //                                      0x00000058;
  // and that should be every thing about a simple external interrupt handling.
  // from efficient an simple code from datasheet reading.
}


uint8_t speed = 100;// 100 ms 
uint8_t ct = 0;
void loop() {
  *___ODR ^= 1<<8; //toggle PE8 on/off
  delay(speed);
}

/* 
  a free and open source way to code custom ISR when it will work. 
  once done timer and compare interrupt are just a formality 
*/
volatile void custom_ISR_EXTIO(void){
  if(speed<=5){
    speed=100;
  }
  else{
    speed-=5;
  }
}
