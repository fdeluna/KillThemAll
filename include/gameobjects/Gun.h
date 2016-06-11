#ifndef Gun_H
#define Gun_H


#include "Weapon.h"
#include "Player.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

using namespace Ogre;

class Gun : public Weapon,Player
{
public:

	//CONSTRUCTOR
	Gun() : _sceneNodeComponentGun(nullptr), _rigidBodyComponentGun(nullptr){};
	Gun(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	//DESTRUCTOR
	~Gun();

	void update(const Ogre::FrameEvent& evt);
	void upgrade();
	void shoot(Ogre::Vector3 direction, Ogre::Vector3 position);

	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponentGun; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponentGun; };
protected:

	SceneNodeComponent* _sceneNodeComponentGun;
	RigidBodyComponent* _rigidBodyComponentGun;
	int numBullet;
};

#endif