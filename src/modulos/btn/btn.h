/*
 * btn.h
 *
 *  Created on: Jun 30, 2024
 *      Author: miche
 */

#ifndef MODULOS_BTN_BTN_H_
#define MODULOS_BTN_BTN_H_

#include <gpio/gpio.h>
#include "pinInterrupt/pinInterrupt.h"

typedef void (*pfBtnHandler)(void*);
typedef void (*pfInterruptHandler)(void*);

class btn: public PinInterrupt {
public:
	enum button_state_t {
		PRESSED, RELEASED
	};
	enum mde_states_t {
		READING, WAIT_DEBOUNCE, VALIDATION
	};

private:
	uint8_t _current_state, _prev_state;
	pfInterruptHandler _intCallback;
	void *_user_ctx;

public:
	btn(uint8_t port, uint8_t bit, activity_t activity, uint8_t interrupt_mode =
			rising_edge, pfInterruptHandler icb = nullptr, void *ctx = nullptr);
	btn(const btn &copybtn);
	~btn(void);
	void mdeUpdate(bool &timer_enable, bool &e_debounce, bool &e_valid,
			bool &e_invalid);

	void addHandler(pfInterruptHandler icb, void *ctx);
	void GpioHandler(void) override;
};

#endif /* MODULOS_BTN_BTN_H_ */
