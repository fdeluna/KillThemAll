#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameObject.h"
#include "SCeneNodeComponent.h"

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>

class PhysicsManager : public Ogre::Singleton<PhysicsManager> {

public:

	PhysicsManager(Ogre::SceneManager* sceneManager,bool debug);
	~PhysicsManager();

	void updatePhysics(Ogre::Real deltaTime);
	OgreBulletDynamics::DynamicsWorld* getWorld(){ return _world; };

	static PhysicsManager& getSingleton();
	static PhysicsManager* getSingletonPtr();

private:

	bool _debug;

	Ogre::SceneManager* _sceneManager;
	OgreBulletDynamics::DynamicsWorld * _world;
	OgreBulletCollisions::DebugDrawer * _debugDrawer;

};

#endif