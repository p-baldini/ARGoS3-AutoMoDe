#include "AutoMoDeObservers.hpp"

namespace argos {

	/****************************************/
	/****************************************/

	void AutoMoDeObservable::Subscribe(AutoMoDeObserver* observer, const std::string event) {
		m_Observers[event].insert(observer);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeObservable::Unsubscribe(AutoMoDeObserver* observer, const std::string event) {
		m_Observers[event].erase(observer);
	}
}
