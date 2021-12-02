#include "LoggingObserver.h"
#include "Orders.h"
#include "CommandProcessor.h"
#include "GameEngine.h"
#include <iostream>		// used for cin & cout
#include <fstream>

using namespace std;


void testLog() {
	cout << "starting log program" << endl;

	// Opening new logFile
	ofstream gameLog;
	gameLog.open("gamelog.txt");

	// Instantiate observer
	LogObserver* observer = new LogObserver();

	// Instantiate Order subjects (thing I am trying to observe )
	Order* deployObj = new Deploy();
	Order* advanceObj = new Advance();
	Order* bombObj = new Bomb();
	Order* blockadeObj = new Blockade();
	Order* airliftObj = new Airlift();
	Order* negotiateObj = new Negotiate();

	// Instantiate OrdersList subject
	OrdersList* orList = new OrdersList();

	// Instantiate Command subject
	Command* command = new Command("playGame", "");

	// Instantiate CommandProcessor subject
	CommandProcessor* comProObj = new CommandProcessor();

	// Instantiate GameEngine subject
	GameEngine* gameEngine = new GameEngine();

	// Add subjects to observer
	// Make the observer observe the different observable objects of the game

	deployObj->Attach(observer);
	advanceObj->Attach(observer);
	bombObj->Attach(observer);
	blockadeObj->Attach(observer);
	airliftObj->Attach(observer);
	negotiateObj->Attach(observer);

	orList->Attach(observer);
	command->Attach(observer);
	gameEngine->Attach(observer);

			comProObj->Attach(observer);

	// Test run for every subject

	deployObj->execute();
	advanceObj->execute();
	bombObj->execute();
	blockadeObj->execute();
	airliftObj->execute();
	negotiateObj->execute();

	orList->add(deployObj);

	command->saveEffect("effect");

	//comProObj->saveCommand(comObj);

	
	gameEngine->receiveCommand(command);

	cout << "\nAll subjects executed\n" << endl;

	// Delete objects
	delete deployObj;
	advanceObj->~Order();
	bombObj->~Order();
	blockadeObj->~Order();
	airliftObj->~Order();
	negotiateObj->~Order();
	orList->~OrdersList();
	delete gameEngine;
	cout << "subjects deleted" << endl;
	//observer->~LogObserver();
	cout << "observer deleted" << endl;
	cout << "end of log program" << endl;

	delete command;
};