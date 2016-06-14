#ifndef PATHFINDER_H
#define PATHFINDER_H


#include "Map.h"

#include <Ogre.h>

class PathFinder : public Ogre::Singleton<PathFinder>{

public:
	PathFinder();
	PathFinder(Map* map):_currentMap(map){};
	
	void FindPath(Ogre::Vector3 origin, Ogre::Vector3 destiny, std::vector<Node*>& path);

	static PathFinder& getSingleton();
	static PathFinder* getSingletonPtr();


private:
	Map* _currentMap;
	int PathFinder::getDistance(Node* nodeA, Node* nodeB);
};


#endif