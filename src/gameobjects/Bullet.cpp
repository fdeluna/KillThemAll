#include "Bullet.h"


Bullet::Bullet(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager)
{
	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Player", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::PLAYER, _sceneNodeComponent);
	//_rigidBodyComponent->getRigidBody()->isKinematicObject();
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
}


Bullet::~Bullet()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}
