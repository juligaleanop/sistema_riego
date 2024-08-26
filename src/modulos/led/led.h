/*
 * gpio.h
 *
 *  Created on: 16 mayo 2024
 *  Author: Augusto Michelli
 */

#ifndef LED_H_
#define LED_H_

#include "LPC845.h"
#include "gpio/gpio.h"
#include <vector>

class led: public gpio {
private:
	uint8_t _state;

public:
	enum power_t {
		OFF, ON
	};

	led(uint8_t port, uint8_t bit, uint8_t actividad);
	led(const led &copyled);

	uint8_t get_state(void) const;
	void set_state(uint8_t state);
	void toggle(void);

	void set_ON(void);
	void set_OFF(void);

	static void set_RGB(uint8_t R, uint8_t G, uint8_t B,
			std::vector<led> &leds);
};

#endif /* LED_H_ */
