#include "Player.h"
#include "Orders.h"

class Player;

class PlayerStrategy {

public:
	Player* player;

	virtual void issueOrder() = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
};

class HumanPlayerStrategy : virtual public PlayerStrategy {
public:

	HumanPlayerStrategy(Player*);
	void issueOrder() override;
	vector<Territory*> toAttack() override;
	vector<Territory*> toDefend() override;
};

class AggressivePlayerStrategy : virtual public PlayerStrategy {
public:

	AggressivePlayerStrategy(Player* p);
	void issueOrder() override;
	vector<Territory*> toAttack() override;
	vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy : virtual public PlayerStrategy {
public:

	BenevolentPlayerStrategy(Player*);
	void issueOrder() override;
	vector<Territory*> toAttack() override;
	vector<Territory*> toDefend() override;
};

class NeutralPlayerStrategy : virtual public PlayerStrategy {
public:


	NeutralPlayerStrategy(Player*);
	void issueOrder() override;
	vector<Territory*> toAttack() override;
	vector<Territory*> toDefend() override;


};

class CheaterPlayerStrategy : virtual public PlayerStrategy {
public:

	CheaterPlayerStrategy(Player*);
	void issueOrder() override;
	vector<Territory*> toAttack() override;
	vector<Territory*> toDefend() override;
};