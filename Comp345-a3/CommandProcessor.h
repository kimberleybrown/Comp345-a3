#pragma once
#include <iostream>
#include <vector>
#include <map>	
#include "LoggingObserver.h"

using namespace std;

class Command : public ILoggable, public Subject { //a2-part5: Souheil
private:
public:
	Command(string name, string effect);
	~Command(); // destructor

	void saveEffect(string effect); // saves the current statee of the game as an effect of the command

	string name;
	string effect;
	string stringToLog(); //a2-part5: Souheil
};

class TournamentCommand : public Command {
public:
	vector<string> mapFiles;
	vector<string> playerStrategies;
	int numberOfGamesPerMap;
	int numberOfTurnsPerGame;
	TournamentCommand(string, string, vector<string>, vector<string>, int, int);
	~TournamentCommand();
};

class LoadMapCommand : public Command {
public:
	string mapFileName;
	LoadMapCommand(string, string, string);
	~LoadMapCommand();
};

class CommandProcessor : public ILoggable, public Subject { //a2-part5: Souheil
private:
	vector<Command*> commands; // contains a pointer to a collection of Command objects
	vector<Command*> validCommands;
	Command* invalidCommand;
public:
	CommandProcessor(); // default constructor

	~CommandProcessor(); // destructor

	Command* getCommand();

	friend ostream& operator<<(ostream& out, const CommandProcessor& cp);

	string stringToLog(); //a2-part5: Souheil

	void saveCommand(Command command); // stores all commands and effects into a list
protected:
	virtual Command* readCommand();
	void saveCommand(Command* command); // stores all commands and effects into a list
	bool validate(vector<string>);
};
