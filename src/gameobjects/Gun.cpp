#include "Gun.h"


Gun::Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{
	_sceneNodeComponentGun = new SceneNodeComponent(_sceneManager, "Gun", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position, player->getSceneNodeComponent()->getSceneNode());
	_sceneNodeComponentGun->getSceneNode()->setScale(Ogre::Vector3(4, 4, 4));
	_rigidBodyComponentGun = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponentGun);
	addComponent(_sceneNodeComponentGun);
	//addComponent(_rigidBodyComponentGun);
	//player->getSceneNodeComponent()->getSceneNode()->attachObject(_sceneNodeComponentGun->getEntity());
	std::cout << player->getSceneNodeComponent()->getSceneNode()->getName() << std::endl;
	_player = player;
}


Gun::~Gun()
{
	//delete _rigidBodyComponentGun;
	delete _sceneNodeComponentGun;
	Gun::~Gun();
}

void Gun::update(const Ogre::FrameEvent& evt){


}

void Gun::upgrade(){



}
void Gun::shoot(){

	Ogre::Vector3 direction = _player->getPlayerInputComponent()->getMousePositionWeapon() - _player->getSceneNodeComponent()->getSceneNode()->getPosition();
	Ogre::Vector3 directionShoot = direction;

	Ogre::Vector3 position = Ogre::Vector3(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x,
		_player->getSceneNodeComponent()->getSceneNode()->getPosition().y + 2,
		_player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

	Bullet* bullet = new Bullet(_sceneNodeComponentGun->getSceneManager(), position, MESHES[MeshName::BULLETP]);
	bullet->getSceneNodeComponent()->getSceneNode()->setScale(Ogre::Vector3(0.2, 0.2, 0.2));
	directionShoot = direction.normalisedCopy() * 20;	//150 

	bullet->getRigidBodyComponent()->getRigidBody()->setLinearVelocity(directionShoot);
	bullet->getRigidBodyComponent()->getRigidBody()->setGravity(Ogre::Vector3(0, 0, 0));
	bullets.push_back(bullet);

	//Resume Game
	numBullet++;
	WaveManager::getSingletonPtr()->setCountBullets(numBullet);


}