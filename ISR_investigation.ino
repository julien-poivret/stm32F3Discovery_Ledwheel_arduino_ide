/*
    That a simple, fast and memory efficient way 
    to cross the whole milky way of the dicovery board !
*/

//  Physical registers for GPIO switch.
volatile uint32_t* ___GPIOE_MODER = (volatile uint32_t *) 0x48001000;


volatile uint32_t* ___GPIOA_MODER = (volatile uint32_t *) 0x48000000;
volatile uint32_t* ___GPIOA_PUPDR = (volatile uint32_t *) 0x4800000C;
volatile uint32_t* ___GPIOA_IDR = (volatile uint32_t *) 0x48000010;

volatile uint32_t* ___RCC_AHBENR = (volatile uint32_t *) 0x40021014;
volatile uint32_t* ___RCC_APB2ENR = (volatile uint32_t *) 0x40021018;
volatile uint32_t* ___ODR = (volatile uint32_t *) 0x48001014;

//  Physical register for interrupt basic config.
volatile uint32_t* ___EXIT_IMR1 = (volatile uint32_t*) 0x40010400;
volatile uint32_t* ___EXIT_EMR1 = (volatile uint32_t*) 0x40010404;
volatile uint32_t* ___EXIT_RTSR1 = (volatile uint32_t*) 0x40010408;
volatile uint32_t* ___EXIT_FTSR1 = (volatile uint32_t *) 0x4001040C;
volatile uint32_t* ___SYSCFG_EXTI1CR1 = (volatile uint32_t *) 0x40010008;
volatile uint32_t* ___NVIC_ISER = (volatile uint32_t*) 0xE000E100;
volatile uint32_t* ___NVIC_IABR = (volatile uint32_t*) 0xE000E300;

void setup() {
  Serial.begin(9600);
  *___RCC_AHBENR |= 0x220000;        // Enable clock on port E and A  
  *___GPIOE_MODER = 0x55550000;      // Enable all leds on the demo wheel in output mode on GPIO_E.
  *___GPIOA_MODER &= ~0x3;           // Set PA0 (press button) as input on GPIO_A.

  *___GPIOA_PUPDR &= ~0x3;           // no pullup 
  // *___GPIOA_PUPDR |= 0x2;          // Set PA0 in pull-down mode (lvl low when not pressed)

  // setting up interrupt easly from datasheet.
  *___RCC_APB2ENR |= 1;               // Enable Syscfg clock
  *___SYSCFG_EXTI1CR1 &= ~0x7;        // Set PA0 on EXTI0 

  Serial.println("IMR register->");
  *___EXIT_IMR1 |= 1;                // Disable mask bit for EXTI0;
  *___EXIT_EMR1 |= 1;                // Disable mask bit for EXTI0;
  *___EXIT_RTSR1 |= 1;               // Set interrupt in Raising trigger mode ON.
  *___EXIT_FTSR1 &= ~1;              // Set interrupt in Falling trigger mode OFF.

  *___NVIC_ISER |= 0x40;
  *___NVIC_IABR |= 0x40; 

//  NVIC_EnableIRQ(EXTI0_IRQn);
//  NVIC_SetPriority(EXTI0_IRQn, 0);
}

uint32_t speed = 500; // 100 ms 
uint8_t ct = 0;

void loop() {
  *___ODR ^= 1<<8; // toggle PE8 on/off
  Serial.println(*___GPIOA_IDR, BIN);
  delay(speed);
}

void EXTI0_IRQHandler(void){
  Serial.println("plop");
  *___ODR ^= 1<<9; // toggle PE9 on/off
}
