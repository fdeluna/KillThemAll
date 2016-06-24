#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"
#include "RigidBodyComponent.h"
#include "InputManager.h"

#include <Ogre.h>

class PlayerInputComponent : public Component {

public:
	PlayerInputComponent() : _playerBody(nullptr), _sceneManager(nullptr), _speed(0.f){};
	PlayerInputComponent(RigidBodyComponent* body, Ogre::SceneManager* sceneManager) : _playerBody(body), _sceneManager(sceneManager), _inputManager(InputManager::getSingletonPtr()){};
	~PlayerInputComponent(){ _playerBody = nullptr;  _inputManager = nullptr; };

	void update(float deltaTime);

	void move(float deltaTime);
	void lookAt();
	
	Ogre::Vector3 getMousePositionWeapon(){ return positionMouseForWaeapon; };
	void setSpeedPlayer(float speed){ _speed = speed; };
private:	
	Ogre::SceneManager* _sceneManager;
	RigidBodyComponent* _playerBody;	
	InputManager* _inputManager;	
	Ogre::Vector3 positionMouseForWaeapon;
	float _speed = 4;

};

#endif