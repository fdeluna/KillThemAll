#ifndef PATHFINDER_H
#define PATHFINDER_H


#include "Map.h"

#include <Ogre.h>

class PathFinder{

public:
	PathFinder();
	PathFinder(Map* map):_currentMap(map){};


	//std::vector<Node*> FindPath(Ogre::Vector3 origin, Ogre::Vector3 destiny);
	std::vector<Node*> FindPath(Ogre::Vector3 origin, Ogre::Vector3 destiny);


private:
	Map* _currentMap;
	int PathFinder::getDistance(Node* nodeA, Node* nodeB);
};


#endif