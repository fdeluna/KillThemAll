#ifndef ENEMYMINER_H
#define ENEMYMINER_H

#include "Enemy.h"
#include "AudioController.h"
#include "Mine.h"

class EnemyMiner : public Enemy{

public:

	EnemyMiner() : Enemy() {};
	EnemyMiner(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Map* map, int level) : Enemy(sceneManager, position, mesh, nullptr, level), _map(map){};

	void update(float deltaTime);
	void collision(GameObject* gameObject);
	void move(float deltaTime);
	bool attack(float deltaTime);
	//void die() {};
	//void hitted() {};

private:

	Map* _map;
	Mine* _mine;

	Ogre::Vector3 _targetPosition = Ogre::Vector3::ZERO;

};


#endif