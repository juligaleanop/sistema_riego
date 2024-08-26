/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include <cr_section_macros.h>
#include <gpio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	gpio pin0(0, 16, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin1(0, 17, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin2(0, 18, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin3(0, 19, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin4(0, 20, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin5(0, 21, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin6(0, 22, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio pin7(0, 23, gpio::OUTPUT, gpio::OPENCOLECTOR, gpio::HIGH);
	gpio * valvulas[8] = { &pin0, &pin1, &pin2, &pin3, &pin4, &pin5, &pin6, &pin7 };

	while (1) {

	}
	return 0;
}
