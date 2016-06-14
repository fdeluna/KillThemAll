#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerInputComponent.h"

class Player : public GameObject{

public:
	Player() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _playerInput(nullptr){};
	Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Player();

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };

private:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	PlayerInputComponent* _playerInput;
};

#endif