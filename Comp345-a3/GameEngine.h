#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


#include "CommandProcessor.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "MapDriver.h"
#include "LoggingObserver.h"

using namespace std;

enum GameEngineState { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, endGame };
//static const char* enumStateStr[] = { "Start", "Map loaded", "Map validated", "Players added", "Assigned reinforcement", "Issue orders", "Execute orders", "Execute orders", "Assign reinforcement", "Win game", "Exit game", "Start" };

class GameEngine : public ILoggable, public Subject { //a2-part5: Souheil

private:

    GameEngineState currentState;
    CommandProcessor* commandProcessor;
    void loadMap(string);

    //initialized Player Array for the gamePlayer array
    //vector<Player*> playerVector;

public:
    string stringToLog(); //a2-part5: Souheil

    // constructors, assignment operator, destructor
    GameEngine(); // constructor for the GameEngine
    GameEngine(const GameEngine& args);
    GameEngine(vector<Player*>);
    GameEngine(string commandsFileName);
    ~GameEngine(); // destructor for the GameEngine
    GameEngine& operator= (const GameEngine& other) {
        cout << "Assignment operator called" << endl;
        return *this;
    }; // assignment operator for GameEngine

    void startGame();

    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrderPhase();

    void endGame();

    void mainGameLoop();

    void receiveCommand(Command* command);
    void validateMap();
    string mapName;
    int numberOfPlayers;

    Map* mapObject;
    MapLoader* mapLoaderObject;

    vector<Player> playersVector;
    //    vector<Deck> deckVector;
    Deck deck;

    void startTournament(TournamentCommand*);

    // stream operator if necessary
    friend ostream& operator<<(ostream& out, const GameEngine& ge);

};
