#pragma once

#include "LPC845.h"

typedef struct {
	union {
		__IO uint32_t SYST_CSR;
		struct {
			__IO uint32_t ENABLE :1;
			__IO uint32_t TICKINT :1;
			__IO uint32_t CLKSOURCE :1;
			__IO uint32_t RESERVED0 :13;
			__IO uint32_t COUNTFLAG :1;
			__IO uint32_t RESERVED1 :15;
		} bits;
	};
	__IO uint32_t SYST_RVR;
	__IO uint32_t SYST_CVR;
	__IO uint32_t SYST_CALIB;
} systick_t;

typedef void (*pfCallback_t)(void);

#define SYSTICK		((systick_t*)0xE000E010UL)
#define SYST_CSR	SYSTICK->SYST_CSR
#define SYST_EN		SYSTICK->bits.ENABLE
#define TICKINT		SYSTICK->bits.TICKINT
#define CLKSOURCE	SYSTICK->bits.CLKSOURCE
#define COUNTFLAG	SYSTICK->bits.COUNTFLAG
#define SYST_RVR	SYSTICK->SYST_RVR
#define SYST_CVR	SYSTICK->SYST_CVR
#define SYST_CALIB	SYSTICK->SYST_CALIB

#define FREQ_CLOCK		12000000
#define FREQ_CLOCK_kHz	(FREQ_CLOCK/1000)
#define MAX_TICKS		4294967295

#if defined (__cplusplus)
extern "C" {
void SysTick_Handler(void);
}
#endif

#define USING_SYSTICK_CALLBACKS		1	// Si se quiere habilitar los callbacks en el SysTick, dejarlo en 1 o 2.

extern bool flag_btnEnableDebounce_100mS;
extern bool flag_ledBlueEnable_1S;
extern bool flag_ledGreenEnable_5S;

#include <vector>

typedef struct systick_handler_data systick_handler_data_t;
typedef void (*systick_timer_handler_t)(systick_handler_data_t*);

enum time_unit_t {
	MIL, DEC, SEG, MIN
};
#define SYSTICK_DECIMA 		100	// Este valor depende de cada cuanto interrumpe el systick
#define SYSTICK_SEGUNDO		10
#define SYSTICK_MINUTO		60

#define ST_500ms	500
#define ST_1500ms	1500

struct systick_handler_data {
	systick_timer_handler_t handler;
	time_unit_t unit;
	uint32_t counter;
	bool enable;
	bool *event_flag;
	bool auto_recharge;
	bool _init_time;
	uint32_t recharge;
};

extern std::vector<systick_handler_data_t*> systick_timers_handlers;

int8_t init_Systick(uint32_t t_ms, pfCallback_t systickCallbacks = nullptr);
void install_SysTickCallback(pfCallback_t pf);

void add_systick_handler(systick_handler_data_t*);

void timer_enable(systick_handler_data_t &tmr);
void timer_disable(systick_handler_data_t &tmr);
void timer_recharge(systick_handler_data_t &tmr);
void timer_handler(systick_handler_data_t *timer_ctx);
