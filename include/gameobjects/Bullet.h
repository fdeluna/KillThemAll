#ifndef Bullet_H
#define Bullet_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "Player.h"

class Bullet : public GameObject{

public:
	Bullet() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Bullet(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Bullet();

	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponent; };
private:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
};

#endif