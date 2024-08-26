#include "systick.h"

// Flag de habilitacion de conteo
bool flag_btnEnableDebounce_100mS = false;
bool flag_ledGreenEnable_5S = false;
bool flag_ledBlueEnable_1S = false;

// Flag de eventos
bool event_TestSystickMde_btn_100mS = false;
bool event_TestSystickMde_ledVerde_5S = false;
bool event_TestSystickMde_ledAzul_1S = false;

pfCallback_t pfSysTickCallbacks;

int8_t init_Systick(uint32_t t_ms, pfCallback_t systickCallbacks) {
	int8_t ret = -1;
	uint32_t clockTicks;

	clockTicks = FREQ_CLOCK_kHz * t_ms;
	if (clockTicks > MAX_TICKS)
		return ret;

	SYST_RVR = clockTicks - 1;
	SYST_CVR = 0;
	SYST_EN = 1;
	TICKINT = 1;
	CLKSOURCE = 1;
	ret = 0;

	// Usando Callbacks!
	if (systickCallbacks)
		install_SysTickCallback(systickCallbacks);

	return ret;
}

void install_SysTickCallback(pfCallback_t pf) {
	pfSysTickCallbacks = (pfCallback_t) pf;
}

#if USING_SYSTICK_CALLBACKS == 0
// Systick Handler SIN callbacks
#define COUNTER_1SEG	1000

void SysTick_Handler(void){
	static __IO uint16_t countTimeout = COUNTER_1SEG;	// 1000 para 1 segundo

	// Esta parte de codigo es para el ejemplo de "test_systick.cpp" ----------------------------
	countTimeout--;
	if(!countTimeout){
		countTimeout = COUNTER_1SEG;
		// Aca voy a cambiar el estado de eventos que dependan del vencimiento de este tiempo
		systick_Led_eventFlag = true;
	}
	// ------------------------------------------------------------------------------------------
}

#elif USING_SYSTICK_CALLBACKS == 1

std::vector<systick_handler_data_t*> systick_timers_handlers;

void add_systick_handler(systick_handler_data_t *hdata) {
	systick_timers_handlers.push_back(hdata);
}

// Systick handler y menejo de Timers en C puro
void timer_handler(systick_handler_data_t *timer_ctx) {
	if (!timer_ctx->_init_time) {// Esto solo lo hace la primera vez que entra al handler
		switch (timer_ctx->unit) {
		case MIL:
			break;
		case DEC:
			timer_ctx->counter *= SYSTICK_DECIMA;
			break;
		case SEG:
			timer_ctx->counter *= (SYSTICK_DECIMA * SYSTICK_SEGUNDO);
			break;
		case MIN:
			timer_ctx->counter *= (SYSTICK_DECIMA * SYSTICK_SEGUNDO
					* SYSTICK_MINUTO);
			break;
		}
		timer_ctx->recharge = timer_ctx->counter;
		timer_ctx->_init_time = true;
	}

	if (timer_ctx->enable) {		// Esta activado el timer?
		timer_ctx->counter--;	// Decremento el contador
		if (!timer_ctx->counter) {	// Llegue a 0?
			timer_ctx->enable = false; // Desactivo el timer
			if (timer_ctx->auto_recharge)
				timer_ctx->counter = timer_ctx->recharge; // Si la autorecarga esta habilitada, la aplico
			*(timer_ctx->event_flag) = true;	// Activo el evento del timer
		}
	}
}

void timer_enable(systick_handler_data_t &tmr) {
	tmr.enable = true;
}

void timer_disable(systick_handler_data_t &tmr) {
	tmr.enable = false;
}

void timer_recharge(systick_handler_data_t &tmr) {
	tmr.counter = tmr.recharge;
}

void SysTick_Handler(void) {
	// Esta parte de codigo es para el ejemplo de "test_systick_mde.cpp" ------------------------
	// Se emplea el uso de callbacks pero sin usar PerifericoTemporizado
	for (auto systickHandler : systick_timers_handlers) {
		if (systickHandler->handler)
			systickHandler->handler(systickHandler);
	}
	// ------------------------------------------------------------------------------------------
}

#elif USING_SYSTICK_CALLBACKS == 2
// Systick Handler CON callbacks con PerifericoTemporizado
void SysTick_Handler(void){
	if(pfSysTickCallbacks) pfSysTickCallbacks();
}

#else

#endif

