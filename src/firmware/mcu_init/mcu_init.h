/*
 * mcu_init.h
 *
 *  Created on: 25 abr. 2024
 *      Author: Augusto Michelli
 */

#pragma once

#define SYSTICK_BASETIME_MS		1
#define _ADV_OSC_CFG			0 // Si se quiere configurar el FRO, CLOCK y PLL, habilitar con 1

void init_HW(void);

void init_osc(void);
