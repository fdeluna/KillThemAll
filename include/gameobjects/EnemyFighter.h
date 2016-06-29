#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "Enemy.h"
#include "AudioController.h"

class EnemyFighter : public Enemy{

public:

	EnemyFighter() : Enemy() {};
	EnemyFighter(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player,int level) : Enemy(sceneManager,position,mesh,player,level) {};
	

	void update(float deltaTime);
	void collision(GameObject* gameObject);
	bool attack(float deltaTime);
	//void die() {};
	//void hitted() {};

private:

	// ATTACK
	float _nextAttack= 1;
	float _attackTime = 0;
	
	float _attackSpeed = 7;
	float _backSpeed = 4;
	bool _endAttack = false;

	Ogre::Vector3 _startPositon = Ogre::Vector3::ZERO;
	Ogre::Vector3 _attackPosition = Ogre::Vector3::ZERO;	

};


#endif