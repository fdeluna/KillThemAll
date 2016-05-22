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
	void makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color);


	bool isWakable();
	Ogre::Vector2 getNodePosition(){ return Ogre::Vector2(_sceneNodeComponent->getPosition().x, _sceneNodeComponent->getPosition().z); };
	SceneNodeComponent* getSceneNode(){ return _sceneNodeComponent; };
		
private:
	bool _walkable;
	Ogre::Vector3 _position;
	SceneNodeComponent* _sceneNodeComponent;
};

#endif