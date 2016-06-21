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

	Ogre::Vector3 mousePosition(_player->getPlayerInputComponent()->getMousePositionWeapon());
	Ogre::Vector3 playerPosition(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x, 1, _player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

	Ogre::Vector3 direction = mousePosition - playerPosition;
	Ogre::Vector3 directionShoot = direction.normalisedCopy();

	//Ogre::Vector3 position = Ogre::Vector3(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x,
	//	1,
	//	_player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

	Bullet* bullet = new Bullet(_sceneNodeComponentGun->getSceneManager(), playerPosition, MESHES[MeshName::BULLETP]);
	bullet->getSceneNodeComponent()->getSceneNode()->setScale(Ogre::Vector3(0.2, 0.2, 0.2));		
	bullet->getRigidBodyComponent()->getRigidBody()->setLinearVelocity(directionShoot * 10);
	bullet->getRigidBodyComponent()->getRigidBody()->setGravity(Ogre::Vector3(0, 0, 0));
	bullet->getRigidBodyComponent()->rotate(mousePosition);
	bullets.push_back(bullet);

	//Resume Game
	numBullet++;
	//WaveManager::getSingletonPtr()->setCountBullets(numBullet);
}