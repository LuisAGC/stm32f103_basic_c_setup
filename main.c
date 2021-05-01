#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void) {
	// First, let's ensure that out clock is running off the 
	// crystal oscillator at 72 MHz
	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
	
	// Since our LED is on GPIO bank B, we need to enable
	// the peripheral clock to this GPIO bank in order to use it.
	rcc_periph_clock_enable(RCC_GPIOB);

	// Our test LED is connected to Port B pin 12, so let0s set it as output
	gpio_set_mode(
		GPIOB, 				//Port to be Set
		GPIO_MODE_OUTPUT_2_MHZ,		//Slew rate, slower means less current and noise
		GPIO_CNF_OUTPUT_PUSHPULL,	//Output in push-pull totem pole style driver
		GPIO12				//Port bit to be set
	);

	//Now, let's forever toggle this LED back and forth
	while (true){
		gpio_toggle(GPIOB, GPIO12);
	}
	
	return 0;
}
