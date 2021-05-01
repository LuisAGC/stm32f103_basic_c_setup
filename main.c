#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */ 
	void sys_tick_handler(void);
	uint64_t millis(void);
	void delay(uint64_t millis);
#ifdef	__cplusplus
}
#endif /* __cplusplus */

static volatile uint64_t _millis = 0;

static void systick_setup(void) {
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	STK_CVR = 0;
	systick_set_reload(rcc_ahb_frequency / 1000 - 1);
	systick_interrupt_enable();
	systick_counter_enable();
}

uint64_t millis(void) {
	return _millis;
}

void sys_tick_handler(void) {
	_millis++;
}

void delay(uint64_t duration) {
	const uint64_t until = millis() + duration;
	while(millis() < until);
}

int main(void) {
	// First, let's ensure that out clock is running off the 
	// crystal oscillator at 72 MHz
	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
	
	systick_setup();
	
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
		delay(1000);
	}
	
	return 0;
}
