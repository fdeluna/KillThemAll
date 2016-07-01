#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "EnemyPathFinderComponent.h"
#include "AudioController.h"

class Enemy : public GameObject{

public:
	Enemy() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _pathFinderComponent(nullptr){};
	Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player, int level, GameObjectType type);
	~Enemy();

	virtual void update(float deltaTime);		
	virtual void move(float deltaTime){};
	virtual bool attack(float deltaTime) { return true; };
	void die() { _state = EnemyState::DIE; };

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };				
protected:	
		
	Player* _player;
	EnemyState _state;
	AudioController* audioController;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;			

	//Variables	
	int _level;
	float _speed = 1.5;//velocidad de movimiento del enemigo
	float _damage = 1;//Danio que hace el enemigo		
	
	//Control	
	bool isAttacking = false;			
	bool attackDistance();	
};




#endif