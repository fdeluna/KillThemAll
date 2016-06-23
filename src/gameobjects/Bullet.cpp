#include "Bullet.h"


Bullet::Bullet(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager)
{
	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Bullet", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::BULLET, _sceneNodeComponent);
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
}


void Bullet::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::ENEMY){
			gameObject->setActive(false);
		}
		Bullet::~Bullet();
	}
}


Bullet::~Bullet()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

