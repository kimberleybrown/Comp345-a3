/** 
* The FileCommandProcessorAdapter class
* This is the Adapter class.
* It adapts a readCommand
*/

#include "FileLineReader.h"
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string commandsFileName)
{
    this->fileLineReader = new FileLineReader(commandsFileName);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete this->fileLineReader;
}

//splits user input on spaces
void parseCommand2(string commandInput, vector<string>& output, char delimiter) {
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

Command* FileCommandProcessorAdapter::readCommand()  {

    string nextLineRaw = "invalid";
    vector<string> fileInputSplit;

    do {

        nextLineRaw = fileLineReader->readLineFromFile();
        parseCommand2(nextLineRaw, fileInputSplit, ' ');

    } while (fileInputSplit.size() > 0 && !validate(fileInputSplit));
    

    return new Command(fileInputSplit.at(0), "");
}