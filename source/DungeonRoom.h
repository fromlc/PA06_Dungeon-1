//------------------------------------------------------------------------------
// DungeonRoom.h : class declaration/definition, version 0.1
// 
// One room in a game dungeon.
// All members are public in this initial version 0.1.
// Each room contains a string description of itself.
// Each room has a point value, given by member variable points.
// Add a dungeon rooms to your game by creating DungeonRoom instances.
// Connect dungeon rooms by setting the pointers.
//------------------------------------------------------------------------------
#pragma once

#include <string>
using std::string;

//------------------------------------------------------------------------------
// DungeonNode 
//------------------------------------------------------------------------------
class DungeonRoom {
public:
    // pointers to other rooms
    DungeonRoom* pNorth;
    DungeonRoom* pSouth;
    DungeonRoom* pEast;
    DungeonRoom* pWest;

    // text description of this room
    string description;
    // point value for this room
    int points;

    // constructors
    DungeonRoom() { }

    DungeonRoom(const string& _desc, int _points) : 
        description(_desc), points(_points) {

        pNorth = pSouth = pEast = pWest = nullptr;
    }

    // destructor #TODO
    ~DungeonRoom() {
        if (pNorth != nullptr)
            delete pNorth;
    }
};

