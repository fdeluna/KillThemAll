#ifndef ENEMYFIGHTER_H
#define ENEMYFIGHTER_h


#include "Enemy.h"
#include "Enum.h"

class EnemyFighter : public Enemy{

public:
	EnemyFighter() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	EnemyFighter(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	//~EnemyFighter();

	

	void setScale(Ogre::Vector3 scale);
	void die();
	void update(const Ogre::FrameEvent& evt);
	int damageHit(int dmg);
	void levelUp();
	void attack();
	void move();

protected:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;

	



};

#endif