#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerInputComponent.h"
#include "Enum.h"

class Player : public GameObject{

public:
	Player() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Player();


	//FUNTIONS
	bool die();
	void hitted(int damage);
	void levelUp();



	//GETTERS/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponent; };
	PlayerInputComponent* getPlayerInputComponent(){ return _playerInput; };

	int getLife(){ return life; };
	int setLife(int hp){ life = hp; };

protected:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	PlayerInputComponent* _playerInput;

	int lifeMax = 8;
	int life = 8;
	
};

#endif