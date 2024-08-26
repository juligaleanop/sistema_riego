/*
 * Callback.cpp
 *
 *  Created on: May 1, 2024
 *      Author: miche
 */

#include "Callback.h"

std::vector<Callback*> Callback::g_CallbackList;

Callback::Callback(pfCallback_t cb) :
		m_callback(cb) {
	if (m_callback) {
		g_CallbackList.push_back(this);
		cb_enabled = true;
	}

}

Callback::~Callback() {
	// TODO Auto-generated destructor stub
}

void Callback::callback(void) {
	if (m_callback)
		m_callback();
}
