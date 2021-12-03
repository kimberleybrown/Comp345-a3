// Final names of other .h files TBD
#include "GameEngine.h"
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
#include "Orders.h"
#include "Player.h"

#include <string>
#include <filesystem>

vector<Territory> listOfTerritoriesVector;
using namespace std;

// Final names of other .h files TBD
// #include "Player.h"
 // #include "Cards.h"

// Game engine class

//a2-part5: Souheil
//ILoggable stringToLog() for Order
string GameEngine::stringToLog() {
    gameLog.open("gamelog.txt", fstream::app);

    gameLog << "Game State: " << currentState << endl;

    gameLog.close();

    return("Game State: " + currentState);
};

GameEngine::GameEngine()
{
    // default constructor

    this->currentState = start;
    Notify(*this); //a2-part5: Souheil
    this->commandProcessor = new CommandProcessor();
}

GameEngine::GameEngine(string commandsFileName)
{
    // commands filename constructor
    this->currentState = start;
    Notify(*this); //a2-part5: Souheil
    this->commandProcessor = new FileCommandProcessorAdapter(commandsFileName);
}

GameEngine::GameEngine(const GameEngine& other) {
    cout << "Copy constructor called" << endl;
    currentState = other.currentState;
    Notify(*this); //a2-part5: Souheil
} // copy constructor for GameEngine

GameEngine::~GameEngine()
{
    // something here will be a nullptr
    //destructor

}

PlayerStrategy* getStrategyFromString(string strategyString) {

    if (strategyString.compare("Aggressive") == 0 || strategyString.compare("aggressive") == 0)
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

void GameEngine::startTournament(TournamentCommand* tournamentStartCommand) {

    for (int map = 0; map < tournamentStartCommand->mapFiles.size(); map++) {

        LoadMapCommand* loadMapCommand  = new LoadMapCommand("loadMap", "", tournamentStartCommand->mapFiles.at(map));
        receiveCommand(loadMapCommand); //TODO: pass map name

        Command* validateMapCommand = new Command("validateMap", "");
        receiveCommand(validateMapCommand);

        for (int player = 0; player < tournamentStartCommand->playerStrategies.size(); player++) {

            string playerStrat = tournamentStartCommand->playerStrategies.at(player);
            AddPlayerCommand* addPlayerCommand = new AddPlayerCommand("addPlayer", "", getStrategyFromString(playerStrat)); //TODO: pass player name
            receiveCommand(addPlayerCommand);

            delete addPlayerCommand;
        }

        Command* assignCountriesCommand = new Command("assignCountries", "");
        receiveCommand(assignCountriesCommand);

        //now we are in the ass. reinf. state
        for (int game = 0; game < tournamentStartCommand->numberOfGamesPerMap; game++) {
            
            //TODO: probably need to pass the maxTurnsPerGame to the game loop so it knows how many turns it can do in the game
            mainGameLoop();
        }



        delete loadMapCommand;
        delete validateMapCommand;
        delete assignCountriesCommand;
    }
}

void GameEngine::startGame()
{
    getMapNames();
    do {
        /* Get the next command to act on. */
        Command* nextCommand = commandProcessor->getCommand();

        /* Acts on the command. */
        receiveCommand(nextCommand);

        if (currentState == assignReinforcement) {
            mainGameLoop();
        }

    } while (currentState != win);
}

void GameEngine::mainGameLoop() {

    int maxRun = 0;

    while (!this->currentState == win)
    {

        reinforcementPhase();
        issueOrdersPhase();
        executeOrderPhase();

    }
}

void GameEngine::receiveCommand(Command* command)
{
    //commands are only valid depending on the state I am in

    switch (currentState)
    {
    case start:
        if (command->name.compare("loadMap") == 0)
        {
            string mapFileToLoad = ((LoadMapCommand*)command)->mapFileName;
            loadMap(mapFileToLoad);

            // transition states and update currentState
            currentState = mapLoaded;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Map Loaded" << endl;
            command->saveEffect("The map has been loaded");

        }
        else if(command->name.compare("tournament") == 0) {
            
            Notify(*this);
            //currentState = assignReinforcement;
            command->saveEffect("Starting tournament");
            startTournament((TournamentCommand*)command);

        }
        else {
            //invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapLoaded:
        if (command->name.compare("validateMap") == 0)
        {
            // call to validateMap transition
            validateMap();
            // transition states and update currentState
            currentState = mapValidated;
                        
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Map Validated" << endl;
            command->saveEffect("The map has been validated");
        }
        else if (command->name.compare("loadMap") == 0)
        {
            // call to issueOrder transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Map Loaded" << endl;
            command->saveEffect("The map has been loaded");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapValidated:
        // Part 2.3
        // enter players in the game
        if (command->name.compare("addPlayer") == 0)
        {
            numberOfPlayers = 0;
            int desiredPlayers = 0;
            bool validPlayers = false;
            while (!validPlayers) {
//                cout << "How many players would you like to add? Please enter between 2-6 players: " << endl;
//                cin >> desiredPlayers;
                desiredPlayers = 2;
                if (desiredPlayers > 6 || desiredPlayers < 2) {
                    cout << "You must select between 2-6 players." << endl;
                }
                else {
                    validPlayers = true;
                }
            }
            
            int i = 0;
            while (numberOfPlayers < desiredPlayers) {
                // call to validateMap transition
                string playerName = "";
                cout << "Please enter player" << i + 1 << " name: " << endl;

//                cin >> playerName;
                //             addPlayer();
                playerName = "kim";
                string intI = std::to_string(i);
                playerName.append(intI);
                Player* player = new Player(playerName);
                numberOfPlayers++;
                playersVector.push_back(*player);
                cout << "player at " << i << " = " << player->name << endl;
                command->saveEffect("Player " + player->name + " has been added");
                i++;
            }

            // transition states and update currentState
            currentState = playersAdded;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Players Added" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case playersAdded:
        // Part 2.4
        // gamestart command
        if (command->name.compare("assignCountries") == 0)
        {
            // Part 2.4a
            // Distribute countries to players
            bool oddNumberTerritories = false;
            cout << "Now assigning countries..." << endl;
//            cout << "here are the number of countries: " << mapLoaderObject->mapObject->territoryCount << endl;
            int countriesPerPlayer = mapLoaderObject->mapObject->territoryCount / numberOfPlayers;
            if(mapLoaderObject->mapObject->territoryCount % 2 != 0) {
                oddNumberTerritories = true;
            }
//            cout << "each player will be assigned " << countriesPerPlayer << endl;

//            cout << "here are the current players and their countries: " << endl;

//            for (int i = 0; i < playersVector.size(); i++) {
//                cout << "playerVector at " << i << " = " << playersVector.at(i).name << endl;
//            }

            for (int i = 0; i < numberOfPlayers; i++) {
//                cout << "i = " << i << endl;
                playersVector.at(i).listOfTerritoriesOwned.resize(countriesPerPlayer);
//                cout << playersVector.at(i).name << " will receive countries: " << endl;
                
                for (int j = 0; j < countriesPerPlayer; j++) {
                    mapLoaderObject->mapObject->terrVector.at(j + (countriesPerPlayer * i)).owner = &playersVector.at(i);
//                    cout << j + (countriesPerPlayer * i) << endl;
                    playersVector.at(i).listOfTerritoriesOwned.at(j) = &mapLoaderObject->mapObject->terrVector.at(j + (countriesPerPlayer * i));
//                    cout << playersVector.at(i).listOfTerritoriesOwned.at(j)->territoryName << endl;
                }
            }
            
            if(oddNumberTerritories) {
                mapLoaderObject->mapObject->terrVector.at(mapLoaderObject->mapObject->territoryCount - 1).owner = &playersVector.at(0);
                playersVector.at(0).listOfTerritoriesOwned.push_back(&mapLoaderObject->mapObject->terrVector.at(mapLoaderObject->mapObject->territoryCount - 1));
            }
            
            listOfTerritoriesVector.resize(mapLoaderObject->mapObject->territoryCount);
            for(int j = 0; j < mapLoaderObject->mapObject->territoryCount; j++) {
//                listOfTerritoriesVector.push_back(mapLoaderObject->mapObject->terrVector.at(j));
                listOfTerritoriesVector.at(j) = mapLoaderObject->mapObject->terrVector.at(j);
            }
            
//            cout << "here are the number of countries: " << mapLoaderObject->mapObject->territoryCount << endl;

            // Part 2.4b
            // Randomly determine order of players
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

            //cout << "problem?" << endl;

            shuffle(playersVector.begin(), playersVector.end(), default_random_engine(seed));
            //cout << "problem here?" << endl;
            cout << "The order of players will be: " << endl;
            for (int i = 0; i < playersVector.size(); i++) {
                cout << playersVector.at(i).name << endl;
            }

            // Part 2.4c
            // Give 50 initial armies to the players

            for (int i = 0; i < numberOfPlayers; i++) {
                playersVector.at(i).reinforcementPool = 50;
            }

            // Part 2.4d
            // Players draw 2 cards from deck and cards are added to player's hand
            Deck* deck = new Deck();
            Cards card;

            for (int i = 0; i < (numberOfPlayers); i++) {
                playersVector.at(i).playerHand.cardsHandVector.resize(2);
                //                Hand* hand = new Hand();
                //                playersVector.at(i).playerHand = hand;
                for (int j = 0; j < 2; j++) {
                    card = deck->draw();

                    playersVector.at(i).playerHand.cardsHandVector.at(j) = card;
                    cout << "player " << playersVector.at(i).name << " receives card: " << card.display_card() << endl;
                }
            }


            // TODO: switch to "gamestart" phase -> "play" phase
            // transition states and update currentState
            currentState = assignReinforcement;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Assign Reinforcements" << endl;
            command->saveEffect("Armies has been deployed");
        }
        else if (command->name.compare("addPlayer") == 0)
        {
            // call to issueOrder transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Players Added " << endl;
            command->saveEffect("Players have been added");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case assignReinforcement:
        if (command->name.compare("issueOrder") == 0)
        {
            // call to assignCountries transition
            // assignCountries();
            // transition states and update currentState
            currentState = issueOrders;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Issue Orders" << endl;
            command->saveEffect("Order issues have been assigned");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case issueOrders:
        if (command->name.compare("endIssueOrders") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = executeOrders;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Execute Orders" << endl;
        }
        else if (command->name.compare("issueOrder") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = issueOrders;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Issue Orders" << endl;
            command->saveEffect("Execute orders have been deployed");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case executeOrders:
        if (command->name.compare("endExecOrders") == 0)
        {
            // call to endIssueOrders transition
            // endIssueOrders();
            // transition states and update currentState
            currentState = assignReinforcement;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Assign Reinforcements" << endl;
            command->saveEffect("Execute orders have been deployed");
        }
        else if (command->name.compare("execOrder") == 0)
        {
            // call to execOrder transition
            // execOrder();
            // transition states and update currentState
            currentState = executeOrders;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Execute Orders" << endl;
            command->saveEffect("Execute orders have been done");
        }
        else if (command->name.compare("winGame") == 0)
        {
            // call to endExecOrders transition
            // endExecOrders();
            // transition states and update currentState
            currentState = win;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Win" << endl;
            command->saveEffect("The game has been won");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case win:
        if (command->name.compare("endGame") == 0)
        {
            // call to exit game
            endGame();
            // transition states and update currentState
            cout << "You have ended the game" << endl;
            command->saveEffect("The game has been exited");
        }
        else if (command->name.compare("playGame") == 0)
        {
            // call to playGame transition
            // start();
            // transition states and update currentState
            currentState = start;
            Notify(*this); //a2-part5: Souheil
            cout << "Current game state is: Start " << endl;
            command->saveEffect("The game has been restarted");
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

        //case exitGame:
            //if (command == GameEngineCommand::endGame)
            //{
                // call to endGame transition
                // endGame();
                // transition states and update currentStat
                //currentState = exitGame;
                //cout << "Current game state is: " << enumStateStr[GameEngineCommand::endGame] << endl;
            //}
            //else {
                // invalid state transition for current state
                //cout << "A state transition could not be made because the command from this state is invalid." << endl;
            //}
            //break;

    default:
        // The command received was not part of valid commands, print error message
        cout << "The command entered is invalid." << endl;
        break;

    }
}

void GameEngine::loadMap(string mapFileName) {

    string mapPath = "";
    string mapsDirectory = "C:\\Users\\Kimberley\\source\\repos\\Comp345-a3\\Comp345-a3\\maps\\";
   // string path = "/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 3/Comp345-A3/Comp345-A3/maps";
   // string path = "/Users/jvlyndark/maps";

    for (const auto& entry : std::filesystem::directory_iterator(mapsDirectory)) {
        if ((entry.path().filename()).string().compare(mapFileName) == 0) {
            mapPath = (entry.path()).string();
            break;
        }
    }

    this->mapLoaderObject = new MapLoader(mapPath);
}

void GameEngine::validateMap() {
    // validate map selected by user
    cout << "Now validating " << mapName << " map" << endl;
    mapLoaderObject->mapObject->validate();
}

//Calculate player's reinforcement
void GameEngine::reinforcementPhase()
{
    bool check = false;
    int armiesToAllocate = 0;
    double count = 0;
    
    bool controlBonus = false;
    // check each continent for control bonus
    for(int i = 0; i < mapLoaderObject->mapObject->continentCount; i++) {
        controlBonus = false;
        Player* owner = mapLoaderObject->mapObject->contVector.at(i).head->territoryPtr->owner;
        ContinentNode* contNode = mapLoaderObject->mapObject->contVector.at(i).head;
        Territory* terr = mapLoaderObject->mapObject->contVector.at(i).head->territoryPtr;
        for(int j = 0; j < mapLoaderObject->mapObject->contVector.at(i).length; j++) {
            if(owner != terr->owner) {
                controlBonus = false;
                break;
            } else {
                controlBonus = true;
            }
            contNode = contNode->next;
            if(contNode != nullptr) terr = contNode->territoryPtr;
        }
        
        if(controlBonus) {
            cout << endl << endl << "CONTROL BONUS!!!!" << endl;
            int bonusAmount = mapLoaderObject->mapObject->contVector.at(i).armyCount;
            for(int j = 0; j < playersVector.size(); j++) {
                if(owner->name == playersVector.at(j).name) {
                    bonusAmount += owner->getReinforcementPool();
                    owner->setReinforcementPool(bonusAmount);
                }
            }
        }
    }
    
    for (size_t i = 0; i < (playersVector.size()); i++)
    {   //check the player's terriotries
        armiesToAllocate = playersVector.at(i).listOfTerritoriesOwned.size();
//        cout << "armiesToAllocate = " << armiesToAllocate << endl;
        armiesToAllocate = armiesToAllocate / 3;
        
        armiesToAllocate += playersVector.at(i).getReinforcementPool();
//        cout << "total armies allocated = " << armiesToAllocate << endl;
        playersVector[i].setReinforcementPool(armiesToAllocate);
        check = false;
        armiesToAllocate = 0;
        count = 0;
    }
}

void GameEngine::issueOrdersPhase()
{
    for (size_t i = 0; i < playersVector.size(); i++) {
        playersVector[i].issueOrder();
    }
}

void GameEngine::executeOrderPhase()
{

    for (size_t i = 0; i < (playersVector.size()); i++)
    {
        for (size_t j = 0; i < playersVector[i].getOrderList().size(); j++)
        {
            playersVector[i].getOrderList()[j]->execute();
        }
    }
}

void GameEngine::endGame() {
    cout << "You have ended the game. Thanks for playing." << endl;
}
