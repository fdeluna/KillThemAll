#ifndef MAPNODE_H
#define MAPNODE_H

#include "Enum.h"
#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

#include <Ogre.h>


class MapNode : public GameObject{

public:
	MapNode() : _walkable(false), _position(Ogre::Vector3::ZERO){};
	MapNode(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh, Ogre::SceneNode* floor, int x, int y);
	~MapNode();

	bool operator == (MapNode &n){ return _gridX == n.getGridX() && _gridY == n.getGridY(); }

	void setWalkable(bool walkable);
	void setScale(Ogre::Vector3 scale);
	void makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color);


	bool isWakable();
	Ogre::Vector2 getNodePosition(){ return Ogre::Vector2(_sceneNodeComponent->getSceneNode()->getPosition().x, _sceneNodeComponent->getSceneNode()->getPosition().z); };
	SceneNodeComponent* getSceneNode(){ return _sceneNodeComponent; };

	int getTotalCost(){ return _g + _h; };

	int getGridX(){ return _gridX; };
	int getGridY(){ return _gridY; };

	int getG(){ return _g; };
	int getH(){ return _h; };

	void setG(int g){ _g = g; };
	void setH(int h){ _h = h; };

	void  setParent(MapNode* parent){ _parent = parent; };
	MapNode* getParent() { return _parent; };



private:
	bool _walkable;
	Ogre::Vector3 _position;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	int _gridX;
	int _gridY;
	int _g; // distance from starting node
	int _h; // distance form destination node

	MapNode* _parent;
};

#endif