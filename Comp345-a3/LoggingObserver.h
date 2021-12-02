#pragma once
#include <list>
#include <fstream>

using namespace std;

class ILoggable {
public:
	virtual string stringToLog() = 0;
protected:
	ofstream gameLog;
};

class Observer {
public:
	~Observer();
	virtual void Update(ILoggable& log) = 0;
protected:
	Observer();
};

class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable& log);
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;
};

class LogObserver : public Observer {
public:
	LogObserver();
	LogObserver(Subject* s);
	~LogObserver();
	void Update(ILoggable& log);
private:
	Subject* _subject;
};














//class ClockTimer : public Subject, public ILoggable {
//public:
//	ClockTimer();
//	int getHour() { return hour; };
//	int getMinute() { return minute; };
//	int getSecond() { return second; };
//	int getInterval() { return timedInterval; };
//	void start();
//	//void setTimedInterval(int newTimedInterval);
//	//void setTime(int newH, int newM, int newS);
//	void tick();
//	~ClockTimer();
//	string stringToLog();
//private:
//	int hour;
//	int minute;
//	int second;
//	int timedInterval;
//};
