#ifndef Gun_H
#define Gun_H


#include "Weapon.h"
#include "GameObject.h"
#include "Player.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

using namespace Ogre;

class Gun : public Weapon, GameObject
{
public:

	//CONSTRUCTOR
	Gun() : _sceneNodeComponentGun(nullptr), _rigidBodyComponentGun(nullptr){};
	Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	//DESTRUCTOR
	~Gun();

	void update(const Ogre::FrameEvent& evt);
	void upgrade();
	void shoot();

	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponentGun; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponentGun; };
protected:
	
	int _numBullet;
	int _damage = 1;
	Player* _player;
	SceneNodeComponent* _sceneNodeComponentGun;
	RigidBodyComponent* _rigidBodyComponentGun;
};

#endif