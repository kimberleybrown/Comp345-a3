#include "CommandProcessor.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

//a2-part5: Souheil
//ILoggable stringToLog() for Command
string Command::stringToLog() {
	gameLog.open("gamelog.txt", fstream::app);

	gameLog << "Command's Effect: " << this->effect << endl;

	gameLog.close();

	return("Command's Effect: " + this->effect);
};

Command::Command(string name, string effect)
{
	this->name = name;
	this->effect = effect;
}

Command::~Command()
{

}

TournamentCommand::TournamentCommand(string name, string effect, vector<string> mapFiles, vector<string> playerStrategies, int numberOfGames, int numberOfTurns) : Command(name, effect) {
	this->mapFiles = mapFiles;
	this->playerStrategies = playerStrategies;
	this->numberOfGamesPerMap = numberOfGames;
	this->numberOfTurnsPerGame = numberOfTurns;
}

TournamentCommand::~TournamentCommand()
{

}

AddPlayerCommand::AddPlayerCommand(string name, string effect, PlayerStrategy* playerStrategy) : Command(name, effect)
{
	this->playerStrategy = playerStrategy;
}

AddPlayerCommand::~AddPlayerCommand()
{
	delete playerStrategy;
}

LoadMapCommand::LoadMapCommand(string name, string effect, string mapFileName) : Command(name, effect)
{
	this->mapFileName = mapFileName;
}

LoadMapCommand::~LoadMapCommand()
{

}

void Command::saveEffect(string effect) {
	this->effect = effect;
	Notify(*this);
}

CommandProcessor::CommandProcessor()
{
	/* Create a list of all valid commands that can be played. */

	validCommands.push_back(new Command("loadMap", ""));
	validCommands.push_back(new Command("tournament", ""));
	validCommands.push_back(new Command("validateMap", ""));
	validCommands.push_back(new Command("addPlayer", ""));
	validCommands.push_back(new Command("assignCountries", ""));
	validCommands.push_back(new Command("gameStart", ""));
	validCommands.push_back(new Command("issueOrder", ""));
	validCommands.push_back(new Command("endIssueOrders", ""));
	validCommands.push_back(new Command("execOrder", ""));
	validCommands.push_back(new Command("endExecOrders", ""));
	validCommands.push_back(new Command("winGame", ""));
	validCommands.push_back(new Command("endGame", ""));
	validCommands.push_back(new Command("playGame", ""));

	invalidCommand = new Command("invalid", "invalid");
}

CommandProcessor::~CommandProcessor()
{
	for (int i = 0; i < commands.size(); i++) {
		delete commands[i];
	}

	for (int i = 0; i < validCommands.size(); i++) {
		delete validCommands[i];
	}

	delete invalidCommand;
}

/*
* The GameEngine calls this function to get the next commands to act on.
*/
Command* CommandProcessor::getCommand() {

	/* Get a command from the console or a file. */

	Command* nextCommand = readCommand();

	/* Save the command to the list of commands. */

	saveCommand(nextCommand);

	return nextCommand;
}

/*
* Save the command to the commands list.
*/
void CommandProcessor::saveCommand(Command* command)
{
	commands.push_back(command);
	Notify(*this);
}

//splits user input on spaces
void parseCommand(string commandInput, vector<string>& output, char delimiter) {
	output.clear();
	string temp = "";
	for (int i = 0; i < commandInput.length(); ++i) {
		if (commandInput[i] == delimiter) {
			output.push_back(temp);
			temp = "";
		}
		else {
			temp.push_back(commandInput[i]);
		}
	}
	output.push_back(temp);
}

TournamentCommand* buildTournamentCommandObject(vector<string> CmdInput)
{
	vector<string> mapFiles;
	vector<string> playerStrategies;
	int numberOfGamesPerMap;
	int numberOfTurnsPerGame;

	parseCommand(CmdInput.at(2), mapFiles, ',');
	parseCommand(CmdInput.at(4), playerStrategies, ',');

	sscanf_s(CmdInput.at(6).c_str(), "%d", &numberOfGamesPerMap);
	sscanf_s(CmdInput.at(8).c_str(), "%d", &numberOfTurnsPerGame);

	return new TournamentCommand(CmdInput.at(0), "effect??", mapFiles, playerStrategies, numberOfGamesPerMap, numberOfTurnsPerGame);
}

LoadMapCommand* buildLoadMapCommand(vector<string> CmdInput)
{
	return new LoadMapCommand("loadMap", "effect?", CmdInput.at(1));
}

PlayerStrategy* getStrategy(string strategyString) {

	if (strategyString.compare("Aggresive") == 0 || strategyString.compare("aggresive") == 0)
	{
		return new AggressivePlayerStrategy();
	}
	if (strategyString.compare("Neutral") == 0 || strategyString.compare("neutral") == 0)
	{
		return new NeutralPlayerStrategy();
	}
	if (strategyString.compare("Benevolent") == 0 || strategyString.compare("benevolent") == 0)
	{
		return new BenevolentPlayerStrategy();
	}
	if (strategyString.compare("Cheater") == 0 || strategyString.compare("cheater") == 0)
	{
		return new CheaterPlayerStrategy();
	}
	return nullptr;
}

//addPlayer <strategyName>
AddPlayerCommand* buildAddPlayerCommand(vector<string> cmdInput) {

	PlayerStrategy* parsedPlayerStrategy = getStrategy(cmdInput.at(1));

	return new AddPlayerCommand("addPlayer", "effect?", parsedPlayerStrategy);
}

bool strategyNameValid(string strategyName) {
	bool strategyNameValid = false;

	if (strategyName.compare("Aggressive") == 0 || strategyName.compare("aggressive") == 0)
	{
		strategyNameValid = true;
	}
	if (strategyName.compare("Neutral") == 0 || strategyName.compare("neutral") == 0)
	{
		strategyNameValid = true;
	}
	if (strategyName.compare("Benevolent") == 0 || strategyName.compare("benevolent") == 0)
	{
		strategyNameValid = true;
	}
	if (strategyName.compare("Cheater") == 0 || strategyName.compare("cheater") == 0)
	{
		strategyNameValid = true;
	}

	return strategyNameValid;
}

bool validateTournamentCommand(vector<string> tournamentCmdInput) {
	if (tournamentCmdInput.size() != 9) {
		return false;
	}

	vector<string> mapFiles;
	vector<string> playerStrategies;
	int numberOfGamesPerMap;
	int numberOfTurnsPerGame;

	parseCommand(tournamentCmdInput.at(2), mapFiles, ',');
	parseCommand(tournamentCmdInput.at(4), playerStrategies, ',');

	if (sscanf_s(tournamentCmdInput.at(6).c_str(), "%d", &numberOfGamesPerMap) != 1) {
		return false;
	}

	if (sscanf_s(tournamentCmdInput.at(8).c_str(), "%d", &numberOfTurnsPerGame) != 1) {
		return false;
	}

	if (mapFiles.size() < 1 || mapFiles.size() > 5)
		return false;
	
	if (playerStrategies.size() < 2 || playerStrategies.size() > 4)
		return false;

	for (int strat = 0; strat < playerStrategies.size(); strat++) {
		if (!strategyNameValid(playerStrategies.at(strat))) {
			return false;
		}
	}

	if (numberOfGamesPerMap < 1 || numberOfGamesPerMap > 5)
		return false;

	if (numberOfTurnsPerGame < 10 || numberOfTurnsPerGame > 50)
		return false;

	return true;
}

bool validateLoadMapCommand(vector<string> cmdInput) {
	if (cmdInput.size() != 2) {
		return false;
	}
	//todo:  check that this file exists
	return true;
}

bool validateAddPlayerCommand(vector<string> cmdInput) {
	if (cmdInput.size() != 2) {
		return false;
	}
	
	string strategyName = cmdInput.at(1);
	
	return strategyNameValid(cmdInput.at(1));
}

bool CommandProcessor::validate(vector<string> commandInput)
{
	if (commandInput.at(0).compare("tournament") == 0) {
		return validateTournamentCommand(commandInput);
	}
	else if (commandInput.at(0).compare("loadMap") == 0) {
		return validateLoadMapCommand(commandInput);
	}
	else if (commandInput.at(0).compare("addPlayer") == 0) {
		return validateAddPlayerCommand(commandInput);
	}

	for (int i = 0; i < validCommands.size(); i++) {
		if (commandInput.at(0).compare(validCommands[i]->name) == 0)
			return true; 
	}

	return false;
}

/*
* Return the next command, either from a text from or from the keyboard.
*/
Command* CommandProcessor::readCommand() {

	/* Read command from keyboard. */

	string userInputRaw;
	vector<string> userInputSplit;

	do {

		cout << "Enter the next command: " << endl;
		getline(cin, userInputRaw);
		parseCommand(userInputRaw, userInputSplit, ' ');

	} while (userInputSplit.size() > 0 && !validate(userInputSplit));

	if (userInputSplit.at(0).compare("tournament") == 0) {
		return buildTournamentCommandObject(userInputSplit);
	}
	else if (userInputSplit.at(0).compare("loadMap") == 0) {
		return buildLoadMapCommand(userInputSplit);
	}
	else if (userInputSplit.at(0).compare("addPlayer") == 0) {
		return buildAddPlayerCommand(userInputSplit);
	}

	return new Command(userInputSplit.at(0), "");
}

//a2-part5: Souheil
//ILoggable stringToLog() for CommandProcessor
string CommandProcessor::stringToLog() {
	gameLog.open("gamelog.txt", fstream::app);

	//gameLog << "Command: " << userInput << endl;

	gameLog.close();

	return("Command: ");// +userInput);
};
