#ifndef NODE_H
#define NODE_h

#include <Ogre.h>

#include "GameObject.h"
#include "SceneNodeComponent.h"

class Node : public GameObject{

public:
	Node() : _walkable(false), _position(Ogre::Vector3::ZERO){};
	Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh);
	~Node(){ GameObject::~GameObject(); };

	void setWalkable(bool walkable);
	void setScale(Ogre::Vector3 scale);
	bool isWakable();

private:
	bool _walkable;
	Ogre::Vector3 _position;
	SceneNodeComponent* _sceneNodeComponente;
};

#endif