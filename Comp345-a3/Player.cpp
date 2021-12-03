
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
#include <algorithm>
#include "Player.h"
#include "PlayerStrategies.h"
using namespace std;


//Default constructor
Player::Player()
{
	name = "default";
	int reinforcementPool = 0;
	vector<Territory*> territory;
	vector<Cards*> handCard;
	vector<Order*> listOfOrders;
	*neutral = false;
}


//Parametric construtor 
Player::Player(string pname)
{
	name = pname;
}

//Copy constructor (Deep copy)
Player::Player(const Player& p)
{
	this->reinforcementPool = p.reinforcementPool;
	this->name = p.name;
	this->listOfTerritoriesOwned = p.listOfTerritoriesOwned;
	this->handCard = p.handCard;
	this->listOfOrders = p.listOfOrders;
	this->neutral = p.neutral;

}

//Four parmeter constructor
Player::Player(int reinforcementPool, string name, vector<Territory*> t, vector<Cards*> h, vector<Order*> o)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->listOfTerritoriesOwned = t;
	this->handCard = h;
	this->listOfOrders = o;
	this->neutral = new bool(false);
}

//added assignment operator
Player& Player::operator=(const Player& player)
{
	this->name = player.name;
	this->reinforcementPool = player.reinforcementPool;
	this->listOfTerritoriesOwned = player.listOfTerritoriesOwned;
	this->handCard = player.handCard;
	this->listOfOrders = player.listOfOrders;
	this->neutral = player.neutral;
	this->ps = player.ps;
	return *this;
}

// Player destructor
Player::~Player()
{
	for (auto p : handCard)
	{
		delete p;
	}
	handCard.clear();

	for (auto p : listOfTerritoriesOwned)
	{
		//delete p;
	}
	listOfTerritoriesOwned.clear();

	for (auto p : listOfTerritoriesToDefend)
	{
		delete p;
	}
	listOfTerritoriesToDefend.clear();

	for (auto p : listOfTerritoriesToAttack)
	{
		delete p;
	}
	listOfTerritoriesToAttack.clear();

	for (auto p : listOfOrders)
	{
		delete p;
	}
	listOfOrders.clear();

	for (auto p : handCard)
	{
		delete p;
	}
	handCard.clear();
}

string Player::getName() {
	return this->name;
}

void Player::setName(string s) {
	this->name = s;
}

int Player::getReinforcementPool() {
	return this->reinforcementPool;
}

void Player::setReinforcementPool(int i) {
	this->reinforcementPool = i;
}

void Player::setTerritory(Territory t)
{

	this->listOfTerritoriesOwned.push_back(&t);
}


void Player::setStrategy(PlayerStrategy* pStrat) {

	if (ps)
		delete ps;
	ps = pStrat;


}



vector<Territory*> Player::getTerritory()
{
	return listOfTerritoriesOwned;

}


vector<Cards*> Player::getCard()
{
	return handCard;
}



//ToAttack() method return a list of territories
vector<Territory*> Player::toAttack() {

	return ps->toAttack();

}


//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend()
{

	return ps->toDefend();

}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder() {

	ps->issueOrder();

}

bool Player::playerContinentBounds()
{

	cout << "inside playerContinentBounds" << endl;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	for (size_t i = 0; i < listOfTerritoriesOwned.size(); i++)
	{
		int temp = (*listOfTerritoriesOwned[i]).continentID;
		if (temp == c1)
		{
			c1++;
		}
		if (temp == c2)
		{
			c2++;
		}
		if (temp == c3)
		{
			c3++;
		}
		if (temp == c4)
		{
			c4++;
		}
		if (temp == c5)
		{
			c5++;
		}
		if (temp == c6)
		{
			c6++;
		}
	}
	if (c1 == 3) { return true; }
	if (c2 == 3) { return true; }
	if (c3 == 1) { return true; }
	if (c4 == 1) { return true; }
	if (c5 == 1) { return true; }
	if (c6 == 1) { return true; }

	return false;
}

vector<Order*> Player::getOrderList()
{
	return listOfOrders;
}

void Player::setOrder(Order* a)
{
	listOfOrders.push_back(a);
}

void  Player::print()
{
	cout << "this is player:" << name << endl;
}