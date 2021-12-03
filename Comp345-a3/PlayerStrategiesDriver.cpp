#include "PlayerStrategies.h"
#include "Player.h"
#include "PlayerStrategiesDriver.h"

// Criteria for the driver:
// (1) Driver that demonstrates that different players can be assigned different 
// strategies that lead to different behavior using the Strategy design pattern.
//
// (2) Driver that demonstrates that the strategy adopted by a player can be 
// changed dynamically during play.
//
// (3) Driver that demonstrates that the human player makes decisions according
// to user interaction, and computer players make decisions automatically, which
// are both implemented using the strategy pattern. 

void testStrategies() {
	Player* player = new Player();
	Player* player1 = new Player(); // Human
	Player* player2 = new Player(); // Neutral
	Player* player3 = new Player(); // Agressive
	Player* player4 = new Player();	// Benevolent
	Player* player5 = new Player(); // Cheater

	// Here: Different players can be assigned different strategies that lead to
	// different behavior using the Strategy design pattern.
	HumanPlayerStrategy* newHum = new HumanPlayerStrategy(player);
	player1->setStrategy(newHum);

	NeutralPlayerStrategy* newNeu = new NeutralPlayerStrategy(player);
	player2->setStrategy(newNeu);
	player2->issueOrder();

	AggressivePlayerStrategy* newAgr = new AggressivePlayerStrategy(player);
	player3->setStrategy(newAgr);
	player3->issueOrder();

	BenevolentPlayerStrategy* newBen = new BenevolentPlayerStrategy(player);
	player4->setStrategy(newBen);
	player4->issueOrder();

	CheaterPlayerStrategy* newChe = new CheaterPlayerStrategy(player);
	player5->setStrategy(newChe);
	player5->issueOrder();

	// (2) Driver that demonstrates that the strategy adopted by a player can be 
	// changed dynamically during play.
	// Neutral player became Aggressive
	player2->setStrategy(newAgr);

	// (3) The human player makes decisions according to user interaction, and
	// computer players make decisions automatically, both using the strategy pattern.
	// Human player will request input from the user
	player1->issueOrder();

	delete player;
	delete player1;
	delete player2;
	delete player3;
	delete player4;
	delete player5;
	delete newHum;
	delete newNeu;
	delete newAgr;
	delete newChe;
	delete newBen;
};