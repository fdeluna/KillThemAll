#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "SceneNodeComponent.h"
#include "PhysicsManager.h"

#include <OgreBulletCollisionsShape.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Shapes/OgreBulletCollisionsCapsuleShape.h>
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>



class RigidBodyComponent : public Component{
public:
	RigidBodyComponent() :_shape(nullptr), _rigidBody(nullptr){};

	RigidBodyComponent(GameObject* gameObject, GameObjectType type, SceneNodeComponent* sceneNodeComponent);
	~RigidBodyComponent();


	OgreBulletDynamics::RigidBody* getRigidBody(){ return _rigidBody;};
	Ogre::Vector3 getPosition();
	Ogre::Quaternion getOrientation();

	void setWorldPosition(Ogre::Vector3 position);
	void setWorldOrientation(Ogre::Quaternion orientation);
	void translate(Ogre::Vector3 position);
	void rotate(Ogre::Vector3 dest);
		
private:
	SceneNodeComponent* _sceneNodeComponent;
	OgreBulletDynamics::RigidBody *_rigidBody;
	OgreBulletCollisions::CollisionShape *_shape;
};


#endif