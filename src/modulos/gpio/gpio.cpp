/*
 * gpio.cpp
 *
 *  Created on: 25 abr. 2024
 *      Author: Augusto Michelli
 */

#include "gpio.h"

// ===============================================================================================
void inic_gpio(void) {
	// Configura GPIO como salidas, las entradas están configuradas por default
	GPIO->DIRSET[1] |= (PIO1_0 | PIO1_1 | PIO1_2);
	// Salidas como push pull
	IOCON->PIO[IOCON_INDEX_PIO1_0] = (IOCON->PIO[IOCON_INDEX_PIO1_0]
			& ~(IOCON_PIO_OD_MASK)) | IOCON_PIO_OD_(0); // 0 es para pushpull
	IOCON->PIO[IOCON_INDEX_PIO1_1] = (IOCON->PIO[IOCON_INDEX_PIO1_1]
			& ~(IOCON_PIO_OD_MASK)) | IOCON_PIO_OD_(0);
	IOCON->PIO[IOCON_INDEX_PIO1_2] = (IOCON->PIO[IOCON_INDEX_PIO1_2]
			& ~(IOCON_PIO_OD_MASK)) | IOCON_PIO_OD_(0);

	//! apago los leds. Como son activo en bajo, tengo que ponerle un 1
	GPIO->PIN[1] |= (PIO1_0 | PIO1_1 | PIO1_2);

	//! Configuro entrada del boton
	GPIO->DIRCLR[0] |= PIO0_4;
	// Entrada con pull up
	IOCON->PIO[IOCON_INDEX_PIO0_4] = (IOCON->PIO[IOCON_INDEX_PIO0_4]
			& ~(IOCON_PIO_MODE_MASK)) | IOCON_PIO_MODE(2); // 2 es para PULLUP
}

void setPin(uint8_t puerto, uint8_t pin) {
	GPIO->PIN[puerto] |= (1 << pin);
}

void clearPin(uint8_t puerto, uint8_t pin) {
	GPIO->PIN[puerto] &= ~(1 << pin);
}

uint8_t getPin(uint8_t puerto, uint8_t pin, uint8_t activity) {
	uint8_t state = GPIO->B[puerto][pin];
	return activity == ACTIVE_HIGH ? state : !state;
}

void togglePin(uint8_t puerto, uint8_t pin) {
	GPIO->NOT[puerto] |= (1 << pin);
}

// ===============================================================================================

// ===============================================================================================
// +++++ Trabajando con la clase GPIO

gpio::gpio(uint8_t port, uint8_t bit, uint8_t direccion, uint8_t modo,
		uint8_t actividad) :
		m_port(port), m_bit(bit), m_actividad(actividad), m_modo(modo), m_direccion(
				direccion) {
	m_error = OK;
	//! Verificar que el puerto y pin son correctos
	if (m_port > PORT1 || (m_port == PORT0 && m_bit > MAX_PORT0)
			|| (m_port == PORT1 && m_bit > MAX_PORT1)) {
		m_error = ERROR;
		return;
	}

	//! Si no hay error, prender el clock para GPIO0(6), GPIO1(20) e IOCON(18)
	SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK
			| SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK
			| SYSCON_SYSAHBCLKCTRL0_IOCON_MASK);

	//! Si es salida, configurar direccion como output y el IOCON
	if (m_direccion == OUTPUT) {
		SetPinOutMode();
		SetDirOutputs();
	} else { //! Si es entrada, configurar direccion como input y el IOCON
		SetDirInputs();
		SetPinInMode();
	}
}

gpio::gpio(const gpio &copygpio) :
		m_port(copygpio.m_port), m_bit(copygpio.m_bit), m_actividad(
				copygpio.m_actividad), m_modo(copygpio.m_modo), m_direccion(
				copygpio.m_direccion) {
	m_error = OK;
	//! Verificar que el puerto y pin son correctos
	if (m_port > PORT1 || (m_port == PORT0 && m_bit > MAX_PORT0)
			|| (m_port == PORT1 && m_bit > MAX_PORT1)) {
		m_error = ERROR;
		return;
	}

	//! Si no hay error, prender el clock para GPIO0(6), GPIO1(20) e IOCON(18)
	SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK
			| SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK
			| SYSCON_SYSAHBCLKCTRL0_IOCON_MASK);

	//! Si es salida, configurar direccion como output y el IOCON
	if (m_direccion == OUTPUT) {
		SetPinOutMode();
		SetDirOutputs();
	} else { //! Si es entrada, configurar direccion como input y el IOCON
		SetDirInputs();
		SetPinInMode();
	}
}

uint8_t gpio::SetPin(void) {
	if (m_error) {
		if (m_actividad == HIGH) {
			GPIO->B[m_port][m_bit] = ON;
		} else
			GPIO->B[m_port][m_bit] = OFF;
	}
	return m_error;
}

uint8_t gpio::ClrPin(void) {
	if (m_error) {
		if (m_actividad == HIGH) {
			GPIO->B[m_port][m_bit] = OFF;
		} else
			GPIO->B[m_port][m_bit] = ON;
	}
	return m_error;
}

uint8_t gpio::GetPin(void) const {
	if (m_error == OK)
		return m_actividad == HIGH ?
				GPIO->B[m_port][m_bit] : !GPIO->B[m_port][m_bit];
	return m_error;
}

uint8_t gpio::SetPinOutMode(void) {
	uint32_t index = 0;
	if (m_error == OK && m_direccion == OUTPUT) {
		index = m_port == 0 ? IOCON_INDEX_PIO0[m_bit] : IOCON_INDEX_PIO1[m_bit];
	}
	IOCON->PIO[index] = (IOCON->PIO[index] & (~IOCON_PIO_OD_MASK))
			| IOCON_PIO_OD_(m_modo);

	return m_error;
}

uint8_t gpio::SetPinInMode(void) {
	uint32_t index = 0;
	if (m_error == OK && m_direccion == INPUT) {
		index = m_port == 0 ? IOCON_INDEX_PIO0[m_bit] : IOCON_INDEX_PIO1[m_bit];
	}
	IOCON->PIO[index] = (IOCON->PIO[index] & (~IOCON_PIO_MODE_MASK))
			| IOCON_PIO_MODE(m_modo);

	return m_error;
}

uint8_t gpio::SetDirInputs(void) {
	if (m_error == OK) {
		m_direccion = INPUT;
		GPIO->DIRCLR[m_port] = 1 << m_bit;
	}
	return m_error;
}

uint8_t gpio::SetDirOutputs(void) {
	if (m_error == OK) {
		m_direccion = OUTPUT;
		GPIO->DIRSET[m_port] = 1 << m_bit;
	}
	return m_error;
}

uint8_t gpio::SetTogglePin(void) {
	if (m_error) {
		GPIO->NOT[m_port] |= (1 << m_bit);
	}
	return m_error;
}

uint8_t gpio::SetToggleDir(void) {
	if (m_error) {
		GPIO->DIRNOT[m_port] |= (1 << m_bit);
	}
	return m_error;
}
