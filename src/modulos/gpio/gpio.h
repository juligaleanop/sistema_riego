/*
 * gpio.h
 *
 *  Created on: 25 abr. 2024
 *      Author: Augusto Michelli
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <LPC845.h>

#define PIO0_4 (1<<4)

#define PIO1_0 (1<<0)
#define PIO1_1 (1<<1)
#define PIO1_2 (1<<2)

#define ACTIVE_LOW			0
#define ACTIVE_HIGH			1

void inic_gpio(void);
void setPin(uint8_t puerto, uint8_t pin);
void clearPin(uint8_t puerto, uint8_t pin);
uint8_t getPin(uint8_t puerto, uint8_t pin, uint8_t activity);
void togglePin(uint8_t puerto, uint8_t pin);

class inputs {
public:
	inputs() {
	}
	;
	virtual uint8_t SetDirInputs(void) = 0;
	virtual uint8_t GetPin(void) const = 0;
	virtual uint8_t SetPinOutMode(void) = 0;
	virtual ~inputs() {
	}
	;
};

class outputs {
public:
	outputs() {
	}
	;
	virtual uint8_t SetDirOutputs(void) = 0;
	virtual uint8_t SetPin(void) = 0;
	virtual uint8_t ClrPin(void) = 0;
	virtual uint8_t SetTogglePin(void) = 0;
	virtual uint8_t SetPinInMode(void) = 0;
	virtual ~outputs() {
	}
	;
};

class gpio: public outputs, public inputs {
protected:
	const uint8_t m_port;
	const uint8_t m_bit;
	const uint8_t m_actividad;

	uint8_t m_modo;
	uint8_t m_direccion;
	int8_t m_error;

	const uint8_t IOCON_INDEX_PIO0[32] = { 17, 11, 6, 5, 4, 3, 16, 15, 4, 13, 8,
			7, 2, 1, 18, 10, 9, 0, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
			0, 0, 35 };
	const uint8_t IOCON_INDEX_PIO1[10] = { 36, 37, 38, 41, 42, 43, 46, 49, 31,
			32 };

public:
	enum port_t {
		PORT0, PORT1
	};
	enum max_bits_port_t {
		MAX_PORT0 = 31, MAX_PORT1 = 9
	};
	enum direction_t {
		INPUT, OUTPUT
	};
	enum power_t {
		OFF, ON
	};
	enum mode_output_t {
		PUSHPULL, OPENCOLECTOR
	};
	enum mode_input_t {
		INACTIVE, PULLDOWN, PULLUP, REPEATER
	};
	enum activity_t {
		LOW, HIGH
	};
	enum interrupt_mode_t {
		rising_edge = 0, falling_edge, any_edge, low_level, high_level
	};
	enum error_t {
		ERROR = 2, OK
	};

	gpio(uint8_t port, uint8_t bit, uint8_t direccion, uint8_t modo,
			uint8_t actividad);
	gpio(const gpio &copygpio);
	gpio& operator=(const gpio &copy);
	uint8_t SetPin(void);
	uint8_t GetPin(void) const;
	uint8_t ClrPin(void);
	uint8_t SetTogglePin(void);
	uint8_t SetDirInputs(void);
	uint8_t SetDirOutputs(void);
	uint8_t SetToggleDir(void);
	uint8_t SetPinOutMode(void);
	uint8_t SetPinInMode(void);
};

#endif /* GPIO_H_ */
