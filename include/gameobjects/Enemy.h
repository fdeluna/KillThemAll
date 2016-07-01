#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "EnemyPathFinderComponent.h"
#include "AudioManager.h"

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
	AudioManager* _audioManager;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;			
	
	int _level;
	float _speed = 2;
	float _damage = 1;
		
	bool isAttacking = false;			
	bool attackDistance();	
};
#endif