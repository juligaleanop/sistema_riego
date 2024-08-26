#include "PerifericoTemporizado.h"

std::vector<PerifericoTemporizado*> g_ListaDePerifericos;

PerifericoTemporizado::PerifericoTemporizado(pf_callback_t pfc) :
		m_HandlerDelPeriferico(pfc) {
}

void PerifericoTemporizado::handlerDelPeriferico() {
	if (m_HandlerDelPeriferico) {
		m_HandlerDelPeriferico();
	}
}

PerifericoTemporizado::~PerifericoTemporizado() {

}

