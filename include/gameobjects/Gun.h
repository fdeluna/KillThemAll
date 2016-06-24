#ifndef Gun_H
#define Gun_H


#include "Weapon.h"
#include "GameObject.h"
#include "Player.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "AudioController.h"

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
	void reload();
	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponentGun; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponentGun; };
	void setCanShoot(bool shoot){ canShoot = shoot; };
	void setReloading(bool reload){ reloading = reload; };
	bool getReloading(){ return reloading; };
	float getVelAtack(){ return velAtack; };
protected:
	
	int _numBullet;
	int _damage = 1;
	Player* _player;
	SceneNodeComponent* _sceneNodeComponentGun;
	RigidBodyComponent* _rigidBodyComponentGun;
	AudioController* audioController;
	bool canShoot = true;
	float velAtack = ATTACKVELOCITIES[AttackVelocity::SLOW];
	float dmg = 2;
	int level = 1;
	float timer;
	int ammo = 12;
	bool reloading = false;
	
};

#endif