/*
 * Callback.h
 *
 *  Created on: May 1, 2024
 *      Author: miche
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "LPC845.h"
#include <vector>

class Callback {
public:
	typedef void (*pfCallback_t)(void);

	Callback(pfCallback_t callback = nullptr);
	virtual ~Callback();

	virtual void callback(void);// Las clases que deriven de Callback deben implementar esto
	static std::vector<Callback*>& getCallbacks(void) {
		return g_CallbackList;
	}

	inline void enable_callback(void) {
		cb_enabled = true;
	}
	inline void disable_callback(void) {
		cb_enabled = false;
	}
	inline bool get_callbackEnabled(void) {
		return cb_enabled;
	}

protected:
	pfCallback_t m_callback;
	static std::vector<Callback*> g_CallbackList;

private:
	bool cb_enabled;
};

#endif /* CALLBACK_H_ */
