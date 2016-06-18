#ifndef Mine_H
#define Mine_H

#include "Weapon.h"
#include "GameObject.h"
#include "Player.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

using namespace Ogre;

class Mine : public Weapon, GameObject
{
public:
	Mine() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Mine(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Mine();

	void update(const Ogre::FrameEvent& evt);
	void shoot();

	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponent; };
protected:

	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	int numBullet;
	Player* _player;
	float timeExplote = 5;
	float timer = 0;
	bool explosion = false;
};
#endif
