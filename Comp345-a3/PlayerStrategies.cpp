#include "PlayerStrategies.h"



HumanPlayerStrategy::HumanPlayerStrategy(Player* p) {
	this->player = p;

}

void HumanPlayerStrategy::issueOrder() {

	int response = 0;

	cout << "What order NUMBER are you issuing?" << endl;
	cout << "1. Deploy" << endl;
	cout << "2. Advance" << endl;
	cout << "3. Airlift" << endl;
	cout << "4. Bomb" << endl;
	cout << "5. Blockade" << endl;
	cout << "6. Negotiate" << endl;

	cin >> response;

	switch (response) {
	case (1): {
		Deploy* newOrder = new Deploy();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	case (2): {
		Advance* newOrder = new Advance();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	case (3): {
		Airlift* newOrder = new Airlift();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	case (4): {
		Bomb* newOrder = new Bomb();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	case (5): {
		Blockade* newOrder = new Blockade();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	case (6): {
		Negotiate* newOrder = new Negotiate();
		cout << newOrder->effect << endl;
		player->setOrder(newOrder);
	}
	default: {
		cout << "ERROR: unrecognized order!" << endl;
	}
	}

}

vector<Territory*> HumanPlayerStrategy::toAttack() {
	vector<Territory*> attackList;
	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		for (auto it2 = (player->get_neighbour_territories(*it).begin()); it2 != player->get_neighbour_territories(*(it)).end(); it2++) {
			if ((*it2)->owner != player) {
				attackList.push_back(*it2);
				(*it2)->owner->listOfTerritoriesOwned.erase(it2);
			}
		}
	}

	return attackList;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
	vector<Territory*> defendList;

	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		defendList.push_back(*it);
	}

	return defendList;
}



AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) {
	this->player = p;
}

void AggressivePlayerStrategy::issueOrder() {

	int highArmy = 0;
	Territory* highTerr = 0;
	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		if ((*it)->armyCount > highArmy) {
			highArmy = (*it)->armyCount;
			highTerr = (*it);
		}
	}

	Deploy* newDeploy = new Deploy(*player, *highTerr, player->reinforcementPool); //will deploy onto the highTerr

	vector<Territory*> attackList = toAttack();
	Territory* tempAtt;
	while (highTerr->armyCount > 1) {

		for (auto it = attackList.begin(); it != attackList.end(); it++) {
			tempAtt = *it;
			Advance* newAdv = new Advance(*player, *highTerr, *tempAtt, highTerr->armyCount);
			player->setOrder(newAdv);
		}
	}

	cout << "Aggressive player has reinforced his strongest territory and attacked all territories it can" << endl;
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {

	vector<Territory*> attackList;
	int highArmy = 0;
	Territory* highTerr = 0;

	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		if ((*it)->armyCount > highArmy) {
			highArmy = (*it)->armyCount;
			highTerr = (*it);
		}
	}

	for (auto it = player->get_neighbour_territories(highTerr).begin(); it != player->get_neighbour_territories(highTerr).end(); it++) {
		if ((*it)->owner != player) {
			attackList.push_back(*it);
		}
	}

	return attackList;
}

vector<Territory*>AggressivePlayerStrategy::toDefend() {

	vector<Territory*> defendList;

	cout << "Aggressive Player does not defend" << endl;

	return defendList;

}



BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) {
	this->player = p;
}


void  BenevolentPlayerStrategy::issueOrder() {

	vector<Territory*> defendList = toDefend();
	while (player->getReinforcementPool() > 0) {
		for (auto it = defendList.begin(); it != defendList.end(); it++) {
			(*it)->armyCount += 1;
			player->setReinforcementPool(player->getReinforcementPool() - 1);
		}
	}
	cout << "Benevolent player has reinforced all their weak territories" << endl;
}

vector<Territory*>  BenevolentPlayerStrategy::toAttack() {
	vector<Territory*> attackList;

	cout << "Benevolent Player does not attack" << endl;

	return attackList;

}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> defendList;

	Territory* begin = *player->listOfTerritoriesOwned.begin();
	int lowCount = begin->armyCount;

	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		if ((*it)->armyCount < lowCount) {
			lowCount = (*it)->armyCount;
		}
	}
	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		if ((*it)->armyCount == lowCount) {
			defendList.push_back(*it);
		}
	}

	return defendList;
}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) {
	this->player = p;

}

void NeutralPlayerStrategy::issueOrder() {
	//do nothing? 

	cout << "The neutral player does nothing. NOTHING." << endl;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {

	vector<Territory*> retTerr{ nullptr };
	cout << "Neutral does not attack" << endl;
	return retTerr;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {

	vector<Territory*> retTerr{ nullptr };
	cout << "Neutral does not defend" << endl;
	return retTerr;
}




CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) {

	this->player = p;

}

void CheaterPlayerStrategy::issueOrder() {

	vector<Territory*> attackList = toAttack();
	vector<Territory*> defendList = toDefend();

	while (player->getReinforcementPool() > 0) {
		for (auto it = defendList.begin(); it != defendList.end(); it++) {
			(*it)->armyCount += 1;
			player->setReinforcementPool(player->getReinforcementPool() - 1);
		}
	}

	for (auto it = attackList.begin(); it != attackList.end(); it++) {
		player->listOfTerritoriesOwned.push_back(*it);
		(*it)->owner = player;
		(*it)->armyCount = 1;
	}

	cout << "The cheater has cheated and conquered all nearby territories." << endl;
}

vector<Territory*> CheaterPlayerStrategy::toAttack() {
	vector<Territory*> attackList;
	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		for (auto it2 = (player->get_neighbour_territories(*it).begin()); it2 != player->get_neighbour_territories(*(it)).end(); it2++) {
			if ((*it2)->owner != player) {
				attackList.push_back(*it2);
				(*it2)->owner->listOfTerritoriesOwned.erase(it2);
			}
		}
	}

	return attackList;
}

vector<Territory*> CheaterPlayerStrategy::toDefend() {
	vector<Territory*> defendList;

	for (auto it = player->listOfTerritoriesOwned.begin(); it != player->listOfTerritoriesOwned.end(); it++) {
		defendList.push_back(*it);
	}

	return defendList;
}