/* 
    add:
        https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
        --->in Arduino/preferances/Additionals Boards Manager.
*/

/*
   Code from the reference manual of the stm32f3 chip and the board user manual of the STM32F303VC MCU.
                                           (On https://www.st.com)
   This is an engineering method for programming microcontroller unit and hardware in general, it's not something
   to know or even to learn by heart, but simply relevant of your understanding of the technical instruction of the chip 
   manufacturer, and your ability to code instructions, some may be disappointed by the specificity, but it's how programming MCU works,
   as an "engineering tool". The purpose of this mem code is to learn fundamental behavior which works on several architectures
   avr pic arm x86 ect... mainly relevant of how hardware behavior works.

                                               Goofy           .;;;.
                                                              :;;;;:'   .;
                                                             :;;: .;;;',;;;; ;:
                                                             :: ,;;;;`;;;:'::;;:,
                                                              :;;;;;; ;;,$$$c` $L
                                                              ;;;;;;;`: $$$$$h $$:
                                                             :;;;;;;;,`J$$$$$$h$$$>
                                                             ;;;;`;';;`3$$$$$$$$$$N
                                                             ;;',;:;;;`3$$$$$$$$$$$>                  cc,
                                                             ',;',;;;;,?$$$$$$$$$$$>                cCC''C
                                                            .;'.:;;';;:'$$$$$$$$$$$E               cCCC;'>
                                                          ,;` ';;',$nn`:?$$$$$$$$$$f               CCCCcC
                                                        ,;`    ':'$$$$$  ?$$$F ?>  >           zdF CCCCC
                                                       ;;`       '$$???$L ?$P  '  .,ur .d$$ u$$$$$ CCC",
                                                     :;;;         $x$h"i7$L"h  d$$$F.d$$$":$$$$$$$$,,c$$
                                                    :;;;          ?$$$k`$$$$fd$$$$ d$$$$ d$$$$$$$$$$$$$F;$L
                                                    ;;;'           ?$$$L`$$$$$$$$k$$$$$b$$$$$$$$$$$$$$F;$$E
                                                   :;;;`          c`"$$$h`$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                                                   ;;;;`         cC $$$$$h "$$$$$$$$$$$$$$$$$FJ$$$P $$$$"
                                                  ,;;;;`        ,C $$$$$$$$h "?$$$$$$$$$$$Cd$.$$F d$P"
                                                  :;;;;`       ,C'9$$$$$$$$$$$u '"?$$$$$$$$$F"  .,cc>
                                                  :;;;;'       CC $$$$$$$$$$h'?$$$-....         d$R"
                                                  :;;;;;       CC,'$$$$$$$$$$" ::  $$$$"
                                                  ';;;;;       "CCc  """""    :;;
                                                   :;;;;`        'CC          :;;'
                                                   `:::'                      ;;;
                                                                             :;;;
                                                                            ';;;;
                                                                            ';;:
                                                                             `

*/


volatile uint32_t* ___GPIOE_MODER = (volatile uint32_t *) 0x48001000;
volatile uint32_t* ___RCC_AHBENR = (volatile uint32_t *) 0x40021014;
volatile uint32_t* ___ODR = (volatile uint32_t *) 0x48001014;

void setup() {
	Serial.begin(9600);
	Serial.println("Program start");
	*___RCC_AHBENR |= 0x200000;  // Enable clock on port E     
	*___GPIOE_MODER = 0x55550000;      // Enable all leds on the demo wheel in output mode.
	Serial.println(*___GPIOE_MODER, HEX);
}

/* 
   the wheel will start to "spin" with an increasing speed over the code progression in time
*/
uint8_t speed = 100;
uint8_t ct = 0;
void loop() {
	while(1){
		*___ODR ^= 1<<(8+ct); // 8 is the bit 8 of the first led of the wheel which start at PE8.
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
