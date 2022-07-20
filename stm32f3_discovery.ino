/* 
    add:
        https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
        --->in Arduino/preferances/Additionals Boards Manager.
*/

/*
   code from the referance manual of the stm32f3 chip and the board user manual of the STM32F303VC MCU.
                                           (found on www.st.com)
*/
volatile uint32_t* ___GPIOE_MODER = (volatile uint32_t *) 0x48001000;
volatile uint32_t* ___RCC_AHBENR = (volatile uint32_t *) 0x40021014;
volatile uint32_t* ___ODR = (volatile uint32_t *) 0x48001014;

void setup() {
	Serial.begin(9600);
	Serial.println("Program start");
	*___RCC_AHBENR |= 0x200000;  // Enable clock on port E     
	*___GPIOE_MODER = 0x55550000;      // Enable all leds on the demo wheel as output.
	Serial.println(*___GPIOE_MODER, HEX);
}

/* 
   the wheel will start to "spin" with an increasing speed over the code progression in time
*/
uint8_t speed = 100;
uint8_t ct = 0;
void loop() {
	while(1){
		*___ODR ^= 1<<(8+ct);
		ct++;
		delay(speed);
		if(ct==9){
			if(speed==10){
				speed=100;
			}else if(speed<75){
				speed-=1;
			}else if(speed<80){
				speed-=5;
			}else{
				speed-=10;
				}
			ct=0;
		}
	}
}
