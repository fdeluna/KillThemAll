#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "Enemy.h"

class EnemyFighter : public Enemy{

public:

	EnemyFighter() : Enemy() {};
	EnemyFighter(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player) : Enemy(sceneManager,position,mesh,player) {};
	

	void collision(GameObject* gameObject);

	//bool attack() { return true; };
	//void die() {};
	//void hitted() {};

private:

};


#endif