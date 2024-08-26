#pragma once

#include <vector>

typedef void (*pf_callback_t)(void);

class PerifericoTemporizado {
protected:
	pf_callback_t m_HandlerDelPeriferico;

public:
	PerifericoTemporizado(pf_callback_t pfc = nullptr);

	virtual void handlerDelPeriferico(void);
	virtual ~PerifericoTemporizado();
};

extern std::vector<PerifericoTemporizado*> g_ListaDePerifericos;
