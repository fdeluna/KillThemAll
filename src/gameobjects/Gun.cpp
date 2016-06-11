#include "Gun.h"


Gun::Gun(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager), Weapon()
{
	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Bullet", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::BULLETR, _sceneNodeComponent);
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);

}


Gun::~Gun()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

void Gun::update(const Ogre::FrameEvent& evt){

	
}

void Gun::upgrade(){

	switch(level){
	
	case 1:
		break;
	}


}
void Gun::shoot(Ogre::Vector3 direction, Ogre::Vector3 position){

	Ogre::Vector3 directionShoot = direction * 10;
	Ogre::String name = Ogre::StringConverter::toString(numBullet + 1);
	numBullet++;
	//La posicion de la bala no es correcta, hay que ponerla en el punto de disparo correcto	
	Bullet* bullet = new Bullet(_sceneNodeComponent->getSceneManager(), Ogre::Vector3(position.x, position.y, position.z), MESHES[Mesh1::TILE]);


	bullet->getSceneNodeComponent()->getSceneNode()->setPosition(position);
	bullet->getSceneNodeComponent()->getSceneNode()->setScale(0.1, 0.1, 0.1);
	//bullet->getRigidBodyComponent()->getRigidBody()->getShape()->getBulletShape()->setLocalScaling(btVector3 (0.1,0.1,0.1));
	directionShoot = direction.normalisedCopy()*50;	//150 
	bullet->getRigidBodyComponent()->getRigidBody()->setLinearVelocity(directionShoot);
	
	//bullet->getRigidBodyComponent()->getRigidBody()->setGravity(Ogre::Vector3(0,0,0));
	bullets.push_back(bullet);

}