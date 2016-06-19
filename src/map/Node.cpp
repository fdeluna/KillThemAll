#include "MapNode.h"

MapNode::MapNode(Ogre::SceneManager* sceneManager, bool walkable, Ogre::Vector3 position, Ogre::String mesh, Ogre::SceneNode* floor, int x, int y) : GameObject(sceneManager), _walkable(walkable), _position(position), _gridX(x), _gridY(y), _parent(nullptr){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "node", mesh, Ogre::Vector3(0.5, 0.25, 0.5), _position);
	addComponent(_sceneNodeComponent);
}

MapNode::~MapNode(){
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

void MapNode::setWalkable(bool walkable){
	_walkable = walkable;
}

void MapNode::setScale(Ogre::Vector3 scale){
	if (_sceneNodeComponent){
		_sceneNodeComponent->getSceneNode()->setScale(scale);
	}
}

bool MapNode::isWakable(){
	return _walkable;
}

void MapNode::makeObstacle(Ogre::Vector3 scale, Ogre::ColourValue color){


	Ogre::Vector3 position = _sceneNodeComponent->getSceneNode()->getPosition() + Ogre::Vector3(0,0.5,0);
	_sceneNodeComponent->getSceneNode()->setPosition(position);
	_sceneNodeComponent->getSceneNode()->setScale(scale);
	_sceneNodeComponent->setDiffuseColor(color);
	_type = GameObjectType::OBSTACLE;

	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponent);	
	addComponent(_rigidBodyComponent);

	_walkable = false;
}