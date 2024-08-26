/*
 * gpio.h
 *
 *  Created on: 16 mayo 2024
 *  Author: Augusto Michelli
 */

#ifndef BTN_H_
#define BTN_H_

#include "LPC845.h"
#include "gpio/gpio.h"

class simpleBtn: public gpio {
public:
	enum button_state_t {
		PRESSED, RELEASED
	};
	enum mde_states_t {
		READING, WAIT_DEBOUNCE, VALIDATION
	};
	typedef void (*pfBtnHandler)(void *ctx);

private:
	uint8_t _current_state, _prev_state;
	void *_user_ctx;
	pfBtnHandler _handler;

public:
	simpleBtn(uint8_t port, uint8_t bit, uint8_t actividad,
			pfBtnHandler handler = nullptr, void *ctx = nullptr);
	simpleBtn(const simpleBtn &copybtn);
	uint8_t get_state(void);
	void update(void);
	void mdeUpdate(bool &timer_enable, bool &e_debounce, bool &e_valid,
			bool &e_invalid);

private:
	inline void delay_debounce(void) const {
		for (int i = 0; i < 3000; i++)
			;
	}

};

#endif /* BTN_H_ */
