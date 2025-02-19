/**
 * @file <src/core/AutoMoDeObservers.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 * 
 * @brief The classes contained in this file define the structure of a Observer oop-pattern. The
 * `AutoMoDeObserver` subscribes to the `AutoMoDeObservable`, requiring to be updated when an event
 * with a specific name fires. The update contains the causing event and a message. When an object
 * of type `AutoMoDeObserver` is destroyed, it needs to un-subscribe to the `AutoMoDeObservable`.
 */
#ifndef AUTOMODE_OBSERVERS_HPP
#define AUTOMODE_OBSERVERS_HPP

#include <map>
#include <set>
#include <string>

namespace argos {
	class AutoMoDeObservable;

	/**
	 * The class that an observer implementation should extend from.
	 */
	class AutoMoDeObserver {
		public:
			/**
			 * Class destroyer. It must unsubscribe to the observable when called.
			 */
			virtual ~AutoMoDeObserver() {
				m_Observable = NULL;
			};

			/**
			 * The function called when an event with the given name fires. It accepts the value
			 * (or message) related to the event.
			 * 
			 * @param[in] event The event that fired.
			 * @param[in] value The message connected with the fired event.
			 */
			virtual void Update(const std::string& event, const std::string& value) = 0;

		protected:
			/**
			 * A reference to the observable class. Used to un-register at destruction.
			 */
			AutoMoDeObservable* m_Observable;
	};

	/**
	 * The class that an observable implementation should extend from.
	 */
	class AutoMoDeObservable {
		public:
			/**
			 * Register an observer to be notified when an event with the given name fires.
			 * 
			 * @param[in] observer The object to be notified when the event fires.
			 * @param[in] event The event that the observer is interested in.
			 */
			virtual void Subscribe(AutoMoDeObserver* observer, const std::string event);

			/**
			 * Stop notifying the given observer when an event with the given name fires.
			 * 
			 * @param[in] observer The object that should not be notified anymore when the event
			 * fires.
			 * @param[in] event The event that the observer is not anymore interested in.
			 */
			virtual void Unsubscribe(AutoMoDeObserver* observer, const std::string event);

		protected:
			/**
			 * For each event, the set of entities that need to be notified.
			 */
			std::map<std::string, std::set<AutoMoDeObserver*>> m_Observers;
	};
}

#endif /* AUTOMODE_OBSERVERS_HPP */
