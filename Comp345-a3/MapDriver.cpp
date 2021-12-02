#include <iostream>		// used for cin & cout
#include <filesystem>
#include <fstream>
#include <string>
//#include <sys/types.h>
#include "Map.h"
//#include "Map.cpp"

using namespace std;
namespace fs = std::filesystem;

void testMap(int index) {

    string mapPath = "";
    string path = "C:\\Users\\Kimberley\\source\\repos\\Comp345-a3\\Comp345-a3\\maps\\";
//    string path = "/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 3/Comp345-A3/Comp345-A3/maps";
     // string path = "/Users/jvlyndark/maps";

    int i = 0;
    
    for(const auto &entry : fs::directory_iterator(mapPath)) {
        i++;
        if(i == index) mapPath = (entry.path()).string();
    }

    cout << "starting Map test..." << endl;
    
    MapLoader* testObject = new MapLoader(mapPath);
    
    // WOW Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/WoW.map");
    
    // TODO: ISSUE -> completes but says map is not valid
    // LOTR2 Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/LOTR2.map");
    
    // Solar Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/solar.map");
    
    // Cow Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/cow.map");
    
    // Canada Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/canada.map");
    
    // sw_baltic Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/sw_baltic.map");
    
    // bigeurope Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/bigeurope.map");
    
    // artic Map (lol)
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/artic.map");
    
    // europass Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/europass.map");
    
    // europe Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/europe.map");
    
    // google Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/google.map");
    
    // MiddleEast-Qatar Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/MiddleEast-Qatar.map");
    
    // sudamerica Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/sudamerica.map");
    
    delete testObject;

}

//TODO: Also call this after a win if there is a replay
void getMapNames() {
    

    cout << "Please enter a Map name from the list and press enter: " << endl;


    // Path name -> must be set to correct local path directory containing map files
      string path = "C:\\Users\\Kimberley\\source\\repos\\Comp345-a3\\Comp345-a3\\maps\\";
   // string path = "/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 3/Comp345-A3/Comp345-A3/maps";
   // string path = "/Users/jvlyndark/maps";

    
    int i = 0;
    for(const auto & entry : fs::directory_iterator(path)) {
        i++;
        string entryPath = (entry.path()).string();
        string mapNameUnformatted = entryPath.substr(path.length(), 100);
        //string mapName = mapNameUnformatted.substr(0, (mapNameUnformatted.length() - 4));
        cout << i << ". " << mapNameUnformatted << endl;
    }
}

