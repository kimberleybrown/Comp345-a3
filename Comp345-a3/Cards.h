#pragma once
#include<iostream>
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>     /* srand, rand */


using namespace std;

class Cards {

	// could have enum values for the card types
	enum cardType { bomb, reinforcement, blockade, airlift, diplomacy };
	cardType ctype;

	public:
	//special order played by the player and sent back to the deck once it is played
		Cards();
		string display_card();
		Cards(int x);
		void play();


};

class Deck {

private:

	// vector that contains a list of Card objects
//	Cards card;
	
	

public:
	Deck();
	void add_to_deck(Cards c);
	void print_deck();
	Cards draw();
 	int getsize();	
	void shuffle_deck();
    vector<Cards> cardsDeckVector;
};


class Hand {
public:
    Hand();
    // vector that contains a list of Card objects
    vector<Cards> cardsHandVector;
private:


};
