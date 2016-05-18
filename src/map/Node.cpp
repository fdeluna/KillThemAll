#include "Node.h"

Node::Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager), _walkable(walkable), _position(position){

	_sceneNodeComponente = new SceneNodeComponent(_sceneManager, mesh, Ogre::Vector3::UNIT_SCALE * 0.25, _position);

	_components.push_back(_sceneNodeComponente);
}

void Node::setWalkable(bool walkable){
	_walkable = walkable;
}

void Node::setScale(Ogre::Vector3 scale){
	if (_sceneNodeComponente){
		_sceneNodeComponente->getSceneNode()->setScale(scale);		
	}
}

bool Node::isWakable(){
	return _walkable;
}

void Node::makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color){
	_sceneNodeComponente->getSceneNode()->setScale(scale);
	_sceneNodeComponente->setDiffuseColor(color);
	_walkable = false;
}