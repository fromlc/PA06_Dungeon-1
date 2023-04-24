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
    // pointers to adjoining rooms
    DungeonRoom* pNorth;
    DungeonRoom* pSouth;
    DungeonRoom* pEast;
    DungeonRoom* pWest;

    // text description of this room
    string description;

    // point value for this room
    int points;

    //--------------------------------------------------------------------------
    // constructors
    //--------------------------------------------------------------------------
    DungeonRoom(const string& _desc, int _points) :
        description(_desc), points(_points) {

        // initialize room pointers
        pNorth = pSouth = pEast = pWest = nullptr;
    }

    //--------------------------------------------------------------------------
    // - assumes the dungeon is one central main room and 4 adjoining rooms
    // - deletes all 4 pointers in main dungeon room
    // - deletes the this pointer to main dungeon room
    // - #TODO use a destructor when implementing an extended map
    //--------------------------------------------------------------------------
    void deleteDungeon() {
        delete pNorth;
        delete pSouth;
        delete pEast;
        delete pWest;
        delete this;
    }
};

