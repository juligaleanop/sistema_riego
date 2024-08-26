#ifndef PININTERRUPT_H_
#define PININTERRUPT_H_

#include "gpio/gpio.h"
#include <LPC845.h>

#if defined (__cplusplus)
extern "C" {
void PININT0_IRQHandler(void);
void PININT1_IRQHandler(void);
void PININT2_IRQHandler(void);
void PININT3_IRQHandler(void);
void PININT4_IRQHandler(void);
void PININT5_IRQHandler(void);
void PININT6_IRQHandler(void);
void PININT7_IRQHandler(void);
}
#endif

class PinInterrupt: public gpio {
public:
	static uint8_t m_cant; /**< Cantidad de PIN INTERRUPT creados globalmente */
	const uint8_t m_interrupt_number; /**< Número de PIN INTERRUPT */
	const uint8_t m_interrupt_mode; /**< Tipo de interrupción del pin */

public:
#define MAX_PININTERRUPT	8

public:
	PinInterrupt(uint8_t port, uint8_t bit, uint8_t gpio_mode,
			activity_t activity, uint8_t intrp_mode);
	void PinInterrupt_Init(void);
	void EnableInterupt(void);
	void DisableInterupt(void);
	virtual void GpioHandler(void) = 0;
	virtual ~PinInterrupt(void);
	inline void setEventInterrupt(bool ev) {
		_event_interrupt = ev;
	}
	inline bool getEventInterrupt(void) {
		return _event_interrupt;
	}
private:
	void PinInterrupt_Enable_clock(void);
	bool _event_interrupt;
};

/** Vector de interrupciones del PIN INTERRUPT */
extern PinInterrupt *g_gpiohandler[MAX_PININTERRUPT];

#endif /* PININTERRUPT_H_ */
