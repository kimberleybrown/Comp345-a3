#include "GameEngineDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"
#include "CardsDriver.h"
#include "MapDriver.h"
#include "LoggingObserver.h"
#include "LoggingObserverDriver.h"
#include "PlayerStrategiesDriver.h"

int main(int argc, char* argv[]) {


	testGameEngine(argc, argv); // uncomment to run GameEngine class
	//OrdersTest(); // uncomment to run Orders class
	//testPlayer(); // uncomment to run Player class
	//testCards(); // uncommment to run Cards class
	//testMap(); // uncomment to run Map class
	//testLog(); // uncomment to run Observer pattern
	//testStrategies(); // uncomment to run PlayerStrategies (p1 of a3)

	return 0;
}
