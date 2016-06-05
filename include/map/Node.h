#ifndef NODE_H
#define NODE_h

#include "Enum.h"
#include "GameObject.h"
#include "SceneNodeComponent.h"

#include "RigidBodyComponent.h"

#include <Ogre.h>


class Node : public GameObject{

public:
	Node() : _walkable(false), _position(Ogre::Vector3::ZERO){};
	Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh,Ogre::SceneNode* floor);
	~Node();
	
	void setWalkable(bool walkable);
	void setScale(Ogre::Vector3 scale);
	void makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color);


	bool isWakable();
	Ogre::Vector2 getNodePosition(){ return Ogre::Vector2(_sceneNodeComponent->getSceneNode()->getPosition().x, _sceneNodeComponent->getSceneNode()->getPosition().z); };
	SceneNodeComponent* getSceneNode(){ return _sceneNodeComponent; };
		
private:
	bool _walkable;
	Ogre::Vector3 _position;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
};

#endif