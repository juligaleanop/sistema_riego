#include "led.h"

led::led(uint8_t port, uint8_t bit, uint8_t actividad) :
		gpio(port, bit, gpio::OUTPUT, gpio::PUSHPULL, actividad) {
	set_state(OFF);
}

led::led(const led &copyled) :
		gpio(copyled), _state(copyled._state) {

}

uint8_t led::get_state(void) const {
	return _state;
}

void led::set_state(uint8_t state) {
	if (state == ON)
		SetPin();
	else
		ClrPin();

	_state = state;
}

void led::toggle(void) {
	SetTogglePin();
	_state = !_state;
}

void led::set_ON(void) {
	SetPin();
	_state = ON;
}
void led::set_OFF(void) {
	ClrPin();
	_state = OFF;
}

void led::set_RGB(uint8_t R, uint8_t G, uint8_t B, std::vector<led> &leds) {
	if (leds.size() == 3) {
		if (R)
			leds.at(0).set_ON();
		else
			leds.at(0).set_OFF();

		if (G)
			leds.at(1).set_ON();
		else
			leds.at(1).set_OFF();

		if (B)
			leds.at(2).set_ON();
		else
			leds.at(2).set_OFF();
	}
}
