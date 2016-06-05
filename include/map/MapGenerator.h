#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "GameObject.h"
#include "Node.h"
#include "Enum.h"
#include "Utils.h"

#include <Ogre.h>
#include <random>

class MapGenerator : public GameObject{

public:

	MapGenerator(Ogre::SceneManager* sceneManager) :GameObject(sceneManager){};
	~MapGenerator(){ cleanMap();  GameObject::~GameObject(); };

	void GenerateMap();
	void cleanMap();
	Ogre::Vector2 _mapCenter;
	SceneNodeComponent* getSceneNodeComponent(){ return planeNode; };
private:
	Ogre::Vector2 _mapSize;	
	
	SceneNodeComponent* planeNode;
	RigidBodyComponent* rigidBodyComponent;
	std::vector< std::vector <Node*>> grid;

	bool isMapAccessible(std::vector< std::vector <bool>> obstacleMap, int currentNumberObstacle);

};

#endif