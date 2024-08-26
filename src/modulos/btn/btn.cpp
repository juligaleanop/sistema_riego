/*
 * btn.cpp
 *
 *  Created on: Jun 30, 2024
 *      Author: miche
 */

#include <btn/btn.h>

btn::btn(uint8_t port, uint8_t bit, activity_t activity, uint8_t interrupt_mode,
		pfInterruptHandler icb, void *ctx) :
		PinInterrupt(port, bit, gpio::PULLUP, activity, interrupt_mode), _intCallback(
				icb), _user_ctx(ctx) {
	_current_state = RELEASED;
	setEventInterrupt(false);
	PinInterrupt_Init();
}

void btn::addHandler(pfInterruptHandler icb, void *ctx) {
	_intCallback = icb;
	_user_ctx = ctx;
}

void btn::GpioHandler(void) {
	// Realiza la acción deseada cuando se produce la interrupción en este pin
	_intCallback(_user_ctx);
}

void btn::mdeUpdate(bool &timer_enable, bool &e_debounce, bool &e_valid,
		bool &e_invalid) {
	static uint8_t state = 0;
	static bool filterEnable = false;
	_current_state = RELEASED;
	uint8_t pinLevel;

	switch (state) {
	case READING: 		// Leo el pin
		if (getEventInterrupt()) {
			setEventInterrupt(false);
			state = WAIT_DEBOUNCE;
			timer_enable = true;
		}
		break;
	case WAIT_DEBOUNCE: // Esperando a que termine el timer de debounce
		if (e_debounce) {
			e_debounce = false;
			timer_enable = false;
			state = VALIDATION;
		}
		break;
	case VALIDATION: // Confirmacion del boton pulsado para generar el evento de valid o invalid
		if ((pinLevel = GetPin())) {
			filterEnable = true;// Activar el filterEnable sirve para que a la siguiente pasada verifique el estado actual y previo
			_current_state = PRESSED;
		} else if (!pinLevel && !filterEnable) { // Si luego del debounce no estaba pulsado y ademas no estaba el filter activado, deja el evento Invalid
			e_invalid = true;
			state = READING;
			EnableInterupt();
		}

		if (filterEnable) {
			if (_prev_state == btn::PRESSED
					&& _current_state == btn::RELEASED) {
				e_valid = true;
				filterEnable = false;
				state = READING;
				EnableInterupt();
			}
			_prev_state = _current_state;
		}
		break;
	}
}

btn::~btn() {
	// TODO Auto-generated destructor stub
}

