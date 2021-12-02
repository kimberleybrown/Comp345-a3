
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
#include <algorithm>
#include "Player.h"
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
	vector<Territory*> listOfTerritoriesToAttack;
    
    for(int i = 0; i < listOfTerritoriesVector.size(); i++) {
        if(listOfTerritoriesVector.at(i).owner != this) {
//            cout << "terr " << listOfTerritoriesVector.at(i).territoryName << " is owned by " << listOfTerritoriesVector.at(i).owner->getName() << " and can be attacked by " << this->name << endl;
            listOfTerritoriesToAttack.push_back(&listOfTerritoriesVector.at(i));
        }
    }
//	for (size_t i = 0; i < listOfTerritoriesOwned.size(); i++)
//	{
//		string temp = getName();
//		if (!temp.compare(listOfTerritoriesOwned[i]->territoryName) == 0)
//			listOfTerritoriesToAttack.push_back(listOfTerritoriesOwned[i]);
//	}
    
	cout << "The list of territories that can be Attacked by " << getName() << endl;
	for (size_t i = 0; i < listOfTerritoriesToAttack.size(); i++)
	{
		cout << "Index " << i << " " << (*listOfTerritoriesToAttack[i]).territoryName << " " << (*listOfTerritoriesToAttack[i]).continentID << endl;
	}
	return listOfTerritoriesToAttack;
}


//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend()
{
	vector<Territory*> listOfTerritoriesToDefend;

	for (size_t i = 0; i < listOfTerritoriesOwned.size(); i++) {
		listOfTerritoriesToDefend.push_back(listOfTerritoriesOwned[i]);
	}


	cout << "The list of territories that can be Defended by " << getName() << endl;
	for (size_t i = 0; i < listOfTerritoriesToDefend.size(); i++)
	{
		cout << "Index " << i << " " << (*listOfTerritoriesToDefend[i]).territoryName << endl;
	}
	return listOfTerritoriesToDefend;
}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder()
{
	//Display territories that can be attack or defend
	vector<Territory*> AttackList;
    AttackList = this->toAttack();
    
	vector<Territory*> DefendList;
	DefendList = this->toDefend();

	int army = getReinforcementPool();
	//Deploy order until no armies left	

	while (army > 0)
	{
		for (size_t i = 0; i < DefendList.size(); i++) {

				cout << "army value now " << army << endl;

				int temp;
				temp = rand() % (army + 1);
				army = army - temp;
				temp += DefendList[i]->armyCount;
				cout << "total amount of armies here now: " << temp << endl;
				DefendList[i]->setArmyAmount(temp);
			
				if (army > 0)
				{
					setReinforcementPool(army);
					cout << "army left to deploy: " << army << endl;
					if (army == 1)
					{
						temp = 1;
						temp += DefendList[i]->armyCount;
						DefendList[i]->setArmyAmount(temp);
						setReinforcementPool(0);
					}
				}
				else {
					setReinforcementPool(0);
					army = 0;
					break;
				}
		}
			
		if(army<=0)
		{ 
			cout << "no armies left, next " << endl;
			break;
		}
	};

	//Advance order Attack

	int actionNumber1 = rand() % AttackList.size();
	int Enemy = AttackList[actionNumber1]->armyCount;

	int actionNumber2 = rand() % DefendList.size();
	int Attack = DefendList[actionNumber2]->armyCount;

	if (Enemy >= Attack)
	{
		Enemy = Enemy - Attack;
		AttackList[actionNumber1]->setArmyAmount(Enemy);
		DefendList[actionNumber2]->setArmyAmount(0);
	}
	else
	{
		Attack = Attack - Enemy;
		AttackList[actionNumber1]->setArmyAmount(Attack);
		DefendList[actionNumber2]->setArmyAmount(0);
		AttackList[actionNumber1]->territoryOwner = getName();
	}
	//Advance order Defend

	int actionNumber3 = rand() % AttackList.size();
	int Defend1 = DefendList[actionNumber1]->armyCount;

	int actionNumber4 = rand() % DefendList.size();
	int Defend2 = DefendList[actionNumber2]->armyCount;

	if (actionNumber3 != actionNumber4)
	{
		DefendList[actionNumber3]->setArmyAmount(0);
		DefendList[actionNumber4]->setArmyAmount(Defend2 + Defend1);
	}
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
