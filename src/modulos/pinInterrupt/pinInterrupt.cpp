#include "pinInterrupt.h"

uint8_t PinInterrupt::m_cant = 0;

PinInterrupt *g_gpiohandler[8];

PinInterrupt::PinInterrupt(uint8_t port, uint8_t bit, uint8_t gpio_mode,
		activity_t activity, uint8_t intrp_mode) :
		gpio(port, bit, gpio::INPUT, gpio_mode, activity), m_interrupt_number(
				m_cant), m_interrupt_mode(intrp_mode) {
	if (m_cant > MAX_PININTERRUPT)
		while (1) {
		};

	g_gpiohandler[m_interrupt_number] = this;

	if (!m_cant)
		PinInterrupt_Enable_clock();

	m_cant++;
}

void PinInterrupt::PinInterrupt_Init(void) {
	//SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32  ;
	NVIC->ISER[0] |= (1 << (24 + m_interrupt_number));

	if (m_interrupt_mode != gpio::low_level
			&& m_interrupt_mode != gpio::high_level)
		PIN_INTERRUPT->ISEL &= ~(1 << m_interrupt_number);
	else
		PIN_INTERRUPT->ISEL |= (1 << m_interrupt_number);

	if (m_interrupt_mode != gpio::falling_edge)
		PIN_INTERRUPT->SIENR |= (1 << m_interrupt_number); /*Activo interrupticion rising edge/de nivel*/
	if (m_interrupt_mode == gpio::falling_edge
			|| m_interrupt_mode == gpio::any_edge
			|| m_interrupt_mode == gpio::high_level)
		PIN_INTERRUPT->SIENF |= (1 << m_interrupt_number); /*Activo interrupcion falling edge / de nivel alto*/
	if (m_interrupt_mode == gpio::low_level)
		PIN_INTERRUPT->CIENF |= (1 << m_interrupt_number); /*Activo interrupcion de nivel bajo*/

	PIN_INTERRUPT->IST |= (1 << m_interrupt_number);
}

void PinInterrupt::EnableInterupt(void) {
	SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32;
}

void PinInterrupt::DisableInterupt(void) {
	SYSCON->PINTSEL[m_interrupt_number] = 0;
}

void PinInterrupt::PinInterrupt_Enable_clock(void) {
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 28);	// 28 = GPIO PIN INTERRUPT
}

PinInterrupt::~PinInterrupt(void) {
	DisableInterupt();
	m_cant--;
}

/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/

void PININT0_IRQHandler(void) {
	g_gpiohandler[0]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 0); /*FINALIZO EL PEDIDO*/
}
void PININT1_IRQHandler(void) {
	g_gpiohandler[1]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 1); /*FINALIZO EL PEDIDO*/
}
void PININT2_IRQHandler(void) {
	g_gpiohandler[2]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 2); /*FINALIZO EL PEDIDO*/
}
void PININT3_IRQHandler(void) {
	g_gpiohandler[3]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 3); /*FINALIZO EL PEDIDO*/
}
void PININT4_IRQHandler(void) {
	g_gpiohandler[4]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 4); /*FINALIZO EL PEDIDO*/
}
void PININT5_IRQHandler(void) {
	g_gpiohandler[5]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 5); /*FINALIZO EL PEDIDO*/
}
void PININT6_IRQHandler(void) {
	g_gpiohandler[6]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 6); /*FINALIZO EL PEDIDO*/
}
void PININT7_IRQHandler(void) {
	g_gpiohandler[7]->GpioHandler();
	PIN_INTERRUPT->IST |= (1 << 7); /*FINALIZO EL PEDIDO*/
}

