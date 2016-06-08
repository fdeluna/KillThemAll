#ifndef NODE_H
#define NODE_H

#include "Enum.h"
#include "GameObject.h"
#include "SceneNodeComponent.h"

#include "RigidBodyComponent.h"

#include <Ogre.h>


class Node : public GameObject{

public:
	Node() : _walkable(false), _position(Ogre::Vector3::ZERO){};
	Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh, Ogre::SceneNode* floor, int x, int y);
	~Node();

	bool operator == (Node &n){ return _gridX == n.getGridX() && _gridY == n.getGridY(); }

	void setWalkable(bool walkable);
	void setScale(Ogre::Vector3 scale);
	void makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color);


	bool isWakable();
	Ogre::Vector2 getNodePosition(){ return Ogre::Vector2(_sceneNodeComponent->getSceneNode()->getPosition().x, _sceneNodeComponent->getSceneNode()->getPosition().z); };
	SceneNodeComponent* getSceneNode(){ return _sceneNodeComponent; };

	int getTotalCost(){ return _sCost + _dCost; };

	int getGridX(){ return _gridX; };
	int getGridY(){ return _gridY; };

	int getSCost(){ return _sCost; };
	int getDcost(){ return _dCost; };

	void setScost(int sCost){ _sCost = sCost; };
	void setDcost(int dCost){ _dCost = dCost; };

	void  setParent(Node* parent){ _parent = parent; };
	Node* getParent() { return _parent; };



private:
	bool _walkable;
	Ogre::Vector3 _position;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	int _gridX;
	int _gridY;
	int _sCost; // distance from starting node
	int _dCost; // distance form destination node

	Node* _parent;
};

#endif