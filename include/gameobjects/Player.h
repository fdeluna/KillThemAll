#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerInputComponent.h"

class Player : public GameObject{

public:
	Player() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Player();

	void update(float deltaTime){ GameObject::update(deltaTime); position = _rigidBodyComponent->getPosition(); };
	// TODO DELETE
	Ogre::Vector3 position;

private:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	PlayerInputComponent* _playerInput;
};

#endif