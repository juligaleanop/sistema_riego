/*
 * mcu_init.cpp
 *
 *  Created on: 25 abr. 2024
 *      Author: Augusto Michelli
 */

#include "mcu_init.h"
#include <gpio/gpio.h>
#include <systick/systick.h>

void init_HW(void) {
	int8_t ret = -1;
	init_osc();
	//init_gpio();

#if USING_SYSTICK_CALLBACKS == 2
	//ret = init_Systick(SYSTICK_BASETIME_MS, MyApp_SystickCallbacks); // systick con callbacks version 1
	ret = init_Systick(SYSTICK_BASETIME_MS, MyApp_PerifericosTemporizados); // systick con callbacks version 2
#else
	ret = init_Systick(SYSTICK_BASETIME_MS); // systick sin callbacks
#endif

	if (ret != 0)
		while (1) {
		}
}

void init_osc(void) {

#if _ADV_OSC_CFG == 1
	// Configuracion del FRO, CLK y PLL
	// 1-Asegura que FRO está encendido
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_FROOUT_PD_MASK;
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_FRO_PD_MASK;
	// 2-Se de frecuencia de FRO
	(*((void (*)(uint32_t freq))(CLOCK_FRO_SETTING_API_ROM_ADDRESS)))(30000);
	// 3-Elige FRO directo como salida de FRO la segunda y tercera instrucciones son necesarias para que el update del FRO tenga efecto
	SYSCON->FROOSCCTRL |= (1<<17);
	SYSCON->FRODIRECTCLKUEN &= ~(uint32_t)SYSCON_FRODIRECTCLKUEN_ENA_MASK;
	SYSCON->FRODIRECTCLKUEN |= (uint32_t)SYSCON_FRODIRECTCLKUEN_ENA_MASK;
	// 4-Se asegura que Main clk está encendido
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_SYSOSC_PD_MASK;
	// Elige System oscilator como clk externo
	SYSCON->EXTCLKSEL &= ~(uint32_t)SYSCON_EXTCLKSEL_SEL_MASK;
	// 5-Elige FRO como main clk
	SYSCON->MAINCLKSEL &= ~(uint32_t)SYSCON_MAINCLKPLLSEL_SEL_MASK;
	SYSCON->MAINCLKUEN &= ~(uint32_t)SYSCON_MAINCLKUEN_ENA_MASK;
	SYSCON->MAINCLKUEN |= (uint32_t)SYSCON_MAINCLKUEN_ENA_MASK;
	SYSCON->MAINCLKPLLSEL &= ~(uint32_t)SYSCON_MAINCLKPLLSEL_SEL_MASK;
	SYSCON->MAINCLKPLLUEN &= ~(uint32_t)SYSCON_MAINCLKPLLUEN_ENA_MASK;
	SYSCON->MAINCLKPLLUEN |= ~(uint32_t)SYSCON_MAINCLKPLLUEN_ENA_MASK;
	// 6-Setea el divisor de clock en 1
	SYSCON->SYSAHBCLKDIV = (uint32_t) 0x01;
#endif

	// Habilita clock de los puertos
	SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK
			| SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK
			| SYSCON_SYSAHBCLKCTRL0_IOCON_MASK);
}

