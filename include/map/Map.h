#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include "Node.h"
#include "Enum.h"
#include "Utils.h"

#include <Ogre.h>
#include <random>

class Map : public GameObject{

public:

	Map(Ogre::SceneManager* sceneManager) :GameObject(sceneManager){};
	~Map(){ cleanMap();  GameObject::~GameObject(); };

	void GenerateMap();
	void cleanMap();

	Ogre::Vector2 _mapCenter;

	Node* nodeFromWorldPosition(Ogre::Vector3 position);
	std::vector<Node*> getNeighbours(Node* node);

	std::vector<std::vector <Node*>> getGrid(){ return grid; };


private:
	Ogre::Vector2 _mapSize;

	SceneNodeComponent* planeNode;
	RigidBodyComponent* rigidBodyComponent;
	std::vector< std::vector <Node*>> grid;

	bool isMapAccessible(std::vector< std::vector <bool>> obstacleMap, int currentNumberObstacle);

};

#endif