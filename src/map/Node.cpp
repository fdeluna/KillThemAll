#include "Node.h"

Node::Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager), _walkable(walkable), _position(position){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager,"node",mesh, Ogre::Vector3(0.45, 0.25, 0.45), _position);

	_components.push_back(_sceneNodeComponent);
}

void Node::setWalkable(bool walkable){
	_walkable = walkable;
}

void Node::setScale(Ogre::Vector3 scale){
	if (_sceneNodeComponent){
		_sceneNodeComponent->setScale(scale);
	}
}

bool Node::isWakable(){
	return _walkable;
}

void Node::makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color){
	Ogre::Vector3 position = _sceneNodeComponent->getPosition();
	_sceneNodeComponent->setPosition(Ogre::Vector3(position.x, position.y + 0.5, position.z));
	_sceneNodeComponent->setScale(scale);
	_sceneNodeComponent->setDiffuseColor(color);
	_walkable = false;
}