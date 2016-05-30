#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "SceneNodeComponent.h"
#include "PhysicsManager.h"

#include <OgreBulletCollisionsShape.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>


class RigidBodyComponent : public Component{
public:
	RigidBodyComponent() :_shape(nullptr), _rigidBody(nullptr){};

	RigidBodyComponent(GameObject* gameObject, GameObjectType type, SceneNodeComponent* sceneNodeComponent);
	~RigidBodyComponent();

	void setWorldPosition(Ogre::Vector3 position);

	void getName(){ std::cout << " RIGID" << std::endl; };

private:
	OgreBulletDynamics::RigidBody *_rigidBody;
	OgreBulletCollisions::CollisionShape *_shape;
};


#endif