#include "Player.h"

Player::Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Player", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.04,0.04,0.04));
	//_sceneNodeComponent->getSceneNode()->pitch(Ogre::Degree(90));
	//_sceneNodeComponent->getSceneNode()->roll(Ogre::Degree(90));
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::PLAYER, _sceneNodeComponent);
	_playerInput = new PlayerInputComponent(_rigidBodyComponent, _sceneManager);
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	addComponent(_playerInput);
}


Player::~Player(){
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

bool Player::die(){

	
	if(life <= 0){
		return true;
	}
	else{
		return false;
	}
}

void Player::hitted(int damage){

	life = life - damage;

}

void Player::potion(){

	if (numPots > 0){
		life = lifeMax;
		numPots--;
		//Resume Game
		countPots++;
	}

}

void Player::levelUp(){

	level++;
	switch (level){
	
	case 10:
		numPots = 2;
	default:
		numPots = 1;
	}
	

}