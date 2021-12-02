#include "LoggingObserver.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// ------------ Observer ------------
Observer::~Observer() {};

Observer::Observer() {};

// ------------ Subject ------------
void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
};

void Subject::Detach(Observer* o)
{
	_observers->remove(o);
};

void Subject::Notify(ILoggable& log)
{
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(log);
};

Subject::Subject()
{
	_observers = new list<Observer*>;
};

Subject::~Subject()
{
	delete _observers;
};

// ------------ LogObserver ------------
LogObserver::LogObserver() {};

LogObserver::LogObserver(Subject* s) {
	// Upon instantiation, attaches itself
	_subject = s;
	_subject->Attach(this);
};

LogObserver::~LogObserver()
{
	// Upon destruction, detaches itself
	_subject->Detach(this);
};

void LogObserver::Update(ILoggable& log)
{
	log.stringToLog();
};










//// ------------ ClockTimer ------------
//ClockTimer::ClockTimer() : hour(0), minute(0), second(0)
//{
//	new LogObserver(this); // attach observer
//};
//
//ClockTimer::~ClockTimer() {};
//
//void ClockTimer::start() {
//	for (int i = 1; i < -timedInterval; i++) {
//		tick();
//	}
//};
//
//void ClockTimer::tick() {
//	second++;
//	if (second >= 60) {
//		minute++; second = 0;
//		if (minute >= 60) {
//			hour++; minute = 0;
//			if (hour >= 24) {
//				hour = 0;
//			}
//		}
//	};
//	
//	//Notify();
//};

//ostream& operator<<(ostream& out, const Subject& subj)
//{
//	// TODO: insert return statement here
//	out << 
//	return out;
//}
