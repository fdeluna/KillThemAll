#include "Bullet.h"


Bullet::Bullet(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager)
{
	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Bullet", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::BULLET, _sceneNodeComponent);
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);

	nodeParticle = sceneManager->createSceneNode("NodeParticula" + _sceneNodeComponent->getEntity()->getName());
	nodeParticle->setScale(0.03, 0.03, 0.03);
	_sceneNodeComponent->getSceneNode()->addChild(nodeParticle);

	partSystem = sceneManager->createParticleSystem("NodeParticula" + _sceneNodeComponent->getEntity()->getName(), "Bullet2");

	nodeParticle->attachObject(partSystem);
	partSystem->setVisible(true);
}

void Bullet::update(float deltaTime){
	_timeToDestroy += deltaTime;

	if (_timeToDestroy > 3){
		_active = false;
	}
}

void Bullet::collision(GameObject* gameObject){
	if (gameObject){		
		if (gameObject->getType() == GameObjectType::ENEMYFIGHTER || gameObject->getType() == GameObjectType::ENEMYMINER){			
			((Enemy*)gameObject)->die();
		}
		setActive(false);
	}
}


Bullet::~Bullet()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

