#pragma once

#include "LPC845.h"
#include "callback/Callback.h"

class Timer: public Callback {
public:
	typedef void (*pfTmrHandler_t)(void*);

protected:
	volatile uint32_t m_TmrRun;
	volatile uint8_t m_TmrBase;
	volatile bool m_TmrEvent;
	volatile bool m_TmrStandBy;
	pfTmrHandler_t m_TmrHandler;
	static std::vector<Timer*> g_TimersList;

private:
	void *m_userCtx;

public:
	enum bases_t {
		DEC, SEG, MIN
	};
	enum ticks_t {
		DECIMAS = 100, SEGUNDOS = 10, MINUTOS = 60
	};
	enum errTimers_t {
		errorTimer, okTimer
	};
	enum standby_t {
		RUN, PAUSE
	};

	Timer(void);
	Timer(const pfTmrHandler_t handler, const bases_t base,
			void *ctx = nullptr);
	virtual ~Timer();

	void callback(void);

	void TimerStart(uint32_t time, const pfTmrHandler_t handler,
			const bases_t base, void *ctx);
	void TimerStart(uint32_t time);
	void TimerStart(void);
	void SetTimer(uint32_t time);
	uint32_t GetTimer(void) const;
	void TimerStop(void);
	void StandByTimer(const standby_t accion);
	void TmrEvent(void);

	Timer& operator=(uint32_t time);
	bool operator!(void);
	bool operator==(uint32_t time);
	friend bool operator==(uint32_t time, Timer &T);

	static std::vector<Timer*>* getTimers(void) {
		return &g_TimersList;
	}
	static void addTimer(Timer *tmr) {
		g_TimersList.push_back(tmr);
	}
};
