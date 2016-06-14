#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Node.h"
#include "SceneNodeComponent.h"
#include "RigidbodyComponent.h"
#include "Player.h"
#include "EnemyPathFinderComponent.h"



class Enemy : public GameObject{

public:
	Enemy() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _pathFinderComponent(nullptr){};
	Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh,Player* player);
	~Enemy();

	//void update(float deltaTime);

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };


protected:	
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;

};




#endif