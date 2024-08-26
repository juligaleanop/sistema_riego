#include "simple_btn.h"

simpleBtn::simpleBtn(uint8_t port, uint8_t bit, uint8_t actividad,
		pfBtnHandler handler, void *ctx) :
		gpio(port, bit, gpio::INPUT, gpio::PULLUP, actividad) {
	_current_state = RELEASED;
	_handler = handler;
	_user_ctx = ctx;
}

simpleBtn::simpleBtn(const simpleBtn &copybtn) :
		gpio(copybtn) {
	_current_state = copybtn._current_state;
	_handler = copybtn._handler;
	_user_ctx = copybtn._user_ctx;
}

uint8_t simpleBtn::get_state(void) {
	_current_state = RELEASED;
	if (GetPin()) {
		delay_debounce();
		if (GetPin())
			_current_state = PRESSED;
	}

	return _current_state;
}

void simpleBtn::update(void) {
	_current_state = get_state();
	if (_prev_state == simpleBtn::PRESSED
			&& _current_state == simpleBtn::RELEASED) {
		_handler(_user_ctx);
	}
	_prev_state = _current_state;
}

void simpleBtn::mdeUpdate(bool &timer_enable, bool &e_debounce, bool &e_valid,
		bool &e_invalid) {
	static uint8_t state = 0;
	static bool filterEnable = false;
	_current_state = RELEASED;
	uint8_t pinLevel;

	switch (state) {
	case READING: 		// Leo el pin
		if ((pinLevel = GetPin())) {
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
		}

		if (filterEnable) {
			if (_prev_state == simpleBtn::PRESSED
					&& _current_state == simpleBtn::RELEASED) {
				e_valid = true;
				filterEnable = false;
				state = READING;
			}
			_prev_state = _current_state;
		}
		break;
	}
}
