//------------------------------------------------------------------------------
// PA06_Dungeon-1.cpp 
//------------------------------------------------------------------------------

#include "DungeonRoom.h"

#include <fstream>
#include <ios>          // std::ios_base::failure exception
#include <iostream>
#include <map>
#include <sstream>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::ifstream;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int DUNGEON_OK = 0;
constexpr int FILE_OPEN_ERROR = -5;
constexpr int FILE_FORMAT_ERROR = -6;

constexpr char GO_NORTH = 'n';
constexpr char GO_SOUTH = 's';
constexpr char GO_EAST  = 'e';
constexpr char GO_WEST  = 'w';
constexpr char GO_AWAY  = 'q';

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
DungeonRoom* getFileRooms(const string& fileName);
void visitDungeon();
DungeonRoom* readFileRoom(ifstream& in);
bool visitAdjoiningRoom(DungeonRoom*& pRoom);
DungeonRoom* getRoomPointer(DungeonRoom* pRoom, char cmd);

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace g {
    int totalPoints = 0;
    DungeonRoom* pMain = nullptr;
}

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    // create a Dungeon with a central Main room and adjoining rooms
    g::pMain = getFileRooms("dungeon.txt");
    visitDungeon();
    
    g::pMain->deleteDungeon();
    g::pMain = nullptr;

    return 0;
}

//------------------------------------------------------------------------------
// - returns pointer to a new dungeon
//------------------------------------------------------------------------------
DungeonRoom* getFileRooms(const string& fileName) {

    ifstream input(fileName);

    if (!input.is_open()) {
        exit(FILE_OPEN_ERROR);
    }

    // return pointer to main room, 1st line in the file
    DungeonRoom* pMainRoom = readFileRoom(input);

    // read room data from file two lines at a time
    if (!pMainRoom) {
        cout << "\nCan't read Dungeon room data from " << fileName << "\n\n";
        exit(FILE_FORMAT_ERROR);
    }

    // set pointers for return
    pMainRoom->pNorth = readFileRoom(input);
    pMainRoom->pNorth->pSouth = pMainRoom;

    pMainRoom->pSouth = readFileRoom(input);
    pMainRoom->pSouth->pNorth = pMainRoom;

    pMainRoom->pEast = readFileRoom(input);
    pMainRoom->pEast->pWest = pMainRoom;

    pMainRoom->pWest = readFileRoom(input);
    pMainRoom->pWest->pEast = pMainRoom;

    // done with file
    input.close();

    return pMainRoom;
}

//------------------------------------------------------------------------------
// - reads room description and points from file (2 lines)
// - returns pointer to new DungeonRoom with file data 
//------------------------------------------------------------------------------
DungeonRoom* readFileRoom(ifstream& in) {

    string roomName;
    string roomPoints;

    if (!getline(in, roomName) || !getline(in, roomPoints)) {
        return nullptr;
    }

    return new DungeonRoom(roomName, stoi(roomPoints));
}


//------------------------------------------------------------------------------
// - visits main room and all adjoining rooms
// - awards room point value
//------------------------------------------------------------------------------
void visitDungeon() {

    // start in the main room
    cout << "You're in a large room, the " << g::pMain->description
        << ", worth " << g::pMain->points << " points.\n";
    cout << "You can go N)orth, S)outh, E)ast, W)est, or Q)uit.\n";

    // start with point value for main room
    g::totalPoints = g::pMain->points;

    DungeonRoom* pRoom = g::pMain;

    // pRoom is a reference param set to player's current room
    while (visitAdjoiningRoom(pRoom)) { }
}

//------------------------------------------------------------------------------
// - visits main room and all adjoining rooms
// - awards room point value
// - always returns true since getRoomPointer() handles quit command 
//------------------------------------------------------------------------------
bool visitAdjoiningRoom(DungeonRoom*& pRoom) {

    DungeonRoom* p = pRoom;

    string direction;
    cout << "\nWhich way? ";
    if (getline(cin, direction)) {

        // command is first character of user input
        p = getRoomPointer(pRoom, tolower(direction.at(0)));

        // pointer set, ready to visit room
        if (!p) {
            cout << "That way is blocked by a pile of rubble\n";
        }
        else {
            cout << "You're in the " << p->description 
                << ", worth " << p->points << " points.\n";

            g::totalPoints += p->points;

            // set reference param
            pRoom = p;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// - visits main room and all adjoining rooms
// - awards room point value
// - exits app on quit command
//------------------------------------------------------------------------------
DungeonRoom* getRoomPointer(DungeonRoom* pRoom, char cmd) {

    DungeonRoom* p = nullptr;

    if (cmd == GO_AWAY) {
        cout << "\nYou scored a total of " 
            << g::totalPoints << " points!\n\n";
        exit(DUNGEON_OK);
    }

    if (cmd == GO_NORTH) {
        p = pRoom->pNorth;
    }
    else if (cmd == GO_SOUTH) {
        p = pRoom->pSouth;
    }
    else if (cmd == GO_EAST) {
        p = pRoom->pEast;
    }
    else if (cmd == GO_WEST) {
        p = pRoom->pWest;
    }
    else {
        // staying in the same room
        cout << "You can go N)orth, S)outh, E)ast, W)est, or Q)uit.\n";
        p = pRoom;
    }

    return p;
}