#include "Timer.h"

std::vector<Timer*> Timer::g_TimersList;

Timer::Timer(void) {
	m_TmrRun = 0;
	m_TmrEvent = 0;
	m_TmrHandler = nullptr;
	m_TmrStandBy = 0;
	m_TmrBase = 0;
	m_userCtx = nullptr;
	// Lo engancho con el tick del sistema
	g_TimersList.push_back(this);
}

Timer::~Timer() {

}

Timer::Timer(const pfTmrHandler_t handler, const bases_t base, void *ctx) {
	m_TmrRun = 0;
	m_TmrEvent = 0;
	m_TmrHandler = handler;
	m_TmrStandBy = 0;
	m_TmrBase = base;
	m_userCtx = ctx;
	// Lo engancho con el tick del sistema
	g_TimersList.push_back(this);
}

void Timer::TimerStart(uint32_t time, const pfTmrHandler_t handler,
		const bases_t base, void *ctx) {
	switch (base) {
	case DEC:
		time *= DECIMAS;
		break;
	case SEG:
		time *= (SEGUNDOS * DECIMAS);
		break;
	case MIN:
		time *= (MINUTOS * SEGUNDOS * DECIMAS);
		break;
	}

	m_TmrBase = base;

	if (time != 0) {  //el tiempo no es 0, lo cargo
		m_TmrRun = time;
		m_TmrEvent = false;
	} else {	//el tiempo es cero, el timer vence automáticamente
		m_TmrRun = 0;
		m_TmrEvent = true;
	}

	m_TmrHandler = handler;
	m_userCtx = ctx;
}

void Timer::TimerStart(uint32_t time) {
	switch (m_TmrBase) {
	case DEC:
		time *= DECIMAS;
		break;
	case SEG:
		time *= (SEGUNDOS * DECIMAS);
		break;
	case MIN:
		time *= (MINUTOS * SEGUNDOS * DECIMAS);
		break;
	}
	if (time != 0) {	//el tiempo no es 0, lo cargo
		m_TmrRun = time;
		m_TmrEvent = false;
	} else {	//el tiempo es cero, el timer vence automáticamente
		m_TmrRun = 0;
		m_TmrEvent = true;
	}
}

void Timer::TimerStart(void) {
	if (m_TmrRun) {
		m_TmrEvent = false;
	} else {
		m_TmrEvent = true;
	}
}

void Timer::callback(void) {
	if (m_TmrRun) {
		if (!m_TmrStandBy) {
			m_TmrRun--;
			if (!m_TmrRun)
				m_TmrEvent = true;
		}
	}
}

void Timer::TimerStop(void) {
	m_TmrRun = 0;
	m_TmrEvent = false;
	m_TmrHandler = nullptr;
	m_TmrStandBy = 0;
	m_TmrBase = 0;
}

void Timer::StandByTimer(const standby_t accion) {
	m_TmrStandBy = accion;
}

uint32_t Timer::GetTimer(void) const {
	uint32_t time = m_TmrRun;
	switch (m_TmrBase) {
	case DEC:
		time /= DECIMAS;
		break;
	case SEG:
		time /= (SEGUNDOS * DECIMAS);
		break;
	case MIN:
		time /= (MINUTOS * SEGUNDOS * DECIMAS);
		break;
	}
	return time;
}

void Timer::SetTimer(uint32_t time) {
	switch (m_TmrBase) {
	case DEC:
		time *= DECIMAS;
		break;
	case SEG:
		time *= (SEGUNDOS * DECIMAS);
		break;
	case MIN:
		time *= (MINUTOS * SEGUNDOS * DECIMAS);
		break;
	}

	m_TmrRun = time;
}

Timer& Timer::operator=(uint32_t time) {
	switch (m_TmrBase) {
	case DEC:
		time *= DECIMAS;
		break;
	case SEG:
		time *= (SEGUNDOS * DECIMAS);
		break;
	case MIN:
		time *= (MINUTOS * SEGUNDOS * DECIMAS);
		break;
	}

	m_TmrRun = time;
	m_TmrEvent = 0;

	return *this;
}

bool Timer::operator==(uint32_t time) {
	if (m_TmrRun == time)
		return true;
	return false;
}

bool operator==(uint32_t t, Timer &T) {
	if (T.m_TmrEvent == t)
		return true;
	return false;
}

bool Timer::operator!(void) {
	return (m_TmrEvent == 1) ? m_TmrEvent = 0, 1 : 0;
}

void Timer::TmrEvent(void) {
	if (m_TmrEvent) {
		m_TmrEvent = 0;
		m_TmrHandler(m_userCtx);
	}
}

