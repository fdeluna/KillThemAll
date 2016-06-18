#ifndef ENEMY_H
#define ENEMY_H

#include "Node.h"
#include "Player.h"
#include "EnemyPathFinderComponent.h"

class Enemy : public GameObject{

public:
	Enemy() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _pathFinderComponent(nullptr){};
	Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh,Player* player);
	virtual ~Enemy();

	virtual void update(float deltaTime);
	virtual void collision(GameObject* gameObject){};

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };


protected:	
	Player* _player;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;
	EnemyState _state;
	
	bool attackDistance();	

	virtual void move(float deltaTime);
	virtual bool attack(float deltaTime) { return true; };
	virtual void die(float deltaTime) {};
	virtual void hitted(float deltaTime) {};
};




#endif