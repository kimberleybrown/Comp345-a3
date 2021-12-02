#include<iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include "Cards.h"

using namespace std;

//default constructor
Cards::Cards() {}

//constructor setting the card type
Cards::Cards(int x) {

    if (x == 0)
        ctype = bomb;
    if (x == 1)
        ctype = reinforcement;
    if (x == 2)
        ctype = blockade;
    if (x == 3)
        ctype = airlift;
    if (x == 4)
        ctype = diplomacy;
}

//empty method for now
void Cards::play() {

    //play the card
}

//displays the type of card
string Cards::display_card() {
    if (ctype == 0)
        return "bomb";

    if (ctype == 1)
        return "reinforcement";

    if (ctype == 2)
        return "blockade";

    if (ctype == 3)
        return "airlift";

    if (ctype == 4)
        return "diplomacy";

    return "";
}

Deck::Deck() {
    // std::cout << "Deck()" << endl;

    for (int count = 0; count < 5; count++) {

        for (int count = 0; count < 5; count++) {
            Cards c = Cards(count);
            add_to_deck(c);
        }
    }
}

//adding the card to the deck
void Deck::add_to_deck(Cards c) {
    cardsDeckVector.push_back(c);
}

void Deck::print_deck() {
    for (int i = 0; i < cardsDeckVector.size(); i++)
        std::cout << cardsDeckVector.at(i).display_card() << endl;
}

void Deck::shuffle_deck() {

};

//randomly draw a card from the card deck
Cards Deck::draw() {

    int random_num;
    srand(time(NULL));
    random_num = rand() % cardsDeckVector.size();
    Cards rand_card = cardsDeckVector.at(random_num);
    cardsDeckVector.erase(cardsDeckVector.begin() + (random_num));

    std::cout << "Player is now drawing a random card from deck... Player drew got the following card: " << random_num << endl;
    std::cout << rand_card.display_card() << endl;

    //                return *rand_card;
    return rand_card;
}

int Deck::getsize() {

    return cardsDeckVector.size();
}

Hand::Hand() {}