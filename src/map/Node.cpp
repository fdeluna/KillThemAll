#include "Node.h"

Node::Node(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh,Ogre::SceneNode* floor) : GameObject(sceneManager), _walkable(walkable), _position(position){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager,"node",mesh, Ogre::Vector3(0.5, 0.25, 0.5), _position);	

	addComponent(_sceneNodeComponent);
}

void Node::setWalkable(bool walkable){
	_walkable = walkable;
}

void Node::setScale(Ogre::Vector3 scale){
	if (_sceneNodeComponent){
		_sceneNodeComponent->getSceneNode()->setScale(scale);		
	}
}

bool Node::isWakable(){
	return _walkable;
}

void Node::makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color){


	Ogre::Vector3 position = _sceneNodeComponent->getSceneNode()->getPosition();	
	_sceneNodeComponent->getSceneNode()->setScale(scale);
	_sceneNodeComponent->setDiffuseColor(color);

	//_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponent);
	//_rigidBodyComponent->setWorldPosition(Ogre::Vector3(position.x,0.5,position.z));
	//addComponent(_rigidBodyComponent);
		
	_walkable = false;
}