#include "Player.h"

Player::Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Player", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::PLAYER, _sceneNodeComponent);
	_playerInput = new PlayerInputComponent(_rigidBodyComponent, _sceneManager);
	_type = GameObjectType::PLAYER;
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	addComponent(_playerInput);
}

Player::~Player(){
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	delete _playerInput;
	GameObject::~GameObject();
}