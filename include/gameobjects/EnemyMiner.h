#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_H

#include "Enemy.h"
#include "AudioController.h"
#include "Mine.h"

class EnemyMiner : public Enemy{

public:

	EnemyMiner() : Enemy() {};
	EnemyMiner(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player, int level) : Enemy(sceneManager, position, mesh, player, level) {};


	void update(float deltaTime);
	void collision(GameObject* gameObject);
	bool attack(float deltaTime);
	//void die() {};
	//void hitted() {};

private:

};


#endif