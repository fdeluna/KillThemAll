#ifndef Gun_H
#define Gun_H


#include "Weapon.h"
#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

using namespace Ogre;

class Gun : public GameObject, Weapon
{
public:

	//CONSTRUCTOR
	Gun() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Gun(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	//DESTRUCTOR
	~Gun();

	void update(const Ogre::FrameEvent& evt);
	void upgrade();
	void shoot(Ogre::Vector3 direction, Ogre::Vector3 position);
	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponent; };
protected:

	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	int numBullet;
};

#endif