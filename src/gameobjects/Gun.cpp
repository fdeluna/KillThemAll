#include "Gun.h"


Gun::Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{
	_sceneNodeComponentGun = new SceneNodeComponent(_sceneManager, "Gun", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position, player->getSceneNodeComponent()->getSceneNode());
	_sceneNodeComponentGun->getSceneNode()->setScale(Ogre::Vector3(4, 4, 4));
	_rigidBodyComponentGun = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponentGun);
	addComponent(_sceneNodeComponentGun);	
	std::cout << player->getSceneNodeComponent()->getSceneNode()->getName() << std::endl;
	_player = player;
	audioController = AudioController::getSingletonPtr();
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

	
	std::cout << level << "leveeeeel gun" << std::endl;
	switch (level)
	{
	case 2:
		velAtack = ATTACKVELOCITIES[AttackVelocity::NORMAL];
		dmg++;
		ammo = 16;
		std::cout << level << velAtack << dmg << ammo << std::endl;

	case 3:
		velAtack = ATTACKVELOCITIES[AttackVelocity::FAST];

		dmg++;
		ammo = 25;
		std::cout << level << velAtack << dmg << ammo << std::endl;

	default:
		break;
	}

}
void Gun::shoot(){

	if (canShoot && ammo >0 && !reloading){
		audioController->playAudio(Audio::SHOOT);

		Ogre::Vector3 mousePosition(_player->getPlayerInputComponent()->getMousePositionWeapon());
		Ogre::Vector3 playerPosition(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x, 1, _player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

		Ogre::Vector3 direction = mousePosition - playerPosition;
		Ogre::Vector3 directionShoot = direction.normalisedCopy();

		//Ogre::Vector3 position = Ogre::Vector3(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x,
		//	1,
		//	_player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

		Bullet* bullet = new Bullet(_sceneNodeComponentGun->getSceneManager(), playerPosition, MESHES[MeshName::BULLETP]);
		bullet->getSceneNodeComponent()->getSceneNode()->setScale(Ogre::Vector3(0.2, 0.2, 0.2));
		bullet->getRigidBodyComponent()->getRigidBody()->setLinearVelocity(directionShoot * 5);
		bullet->getRigidBodyComponent()->getRigidBody()->setGravity(Ogre::Vector3(0, 0, 0));
		bullet->getRigidBodyComponent()->rotate(mousePosition);
		bullets.push_back(bullet);

		//Resume Game
		_numBullet++;
		WaveManager::getSingletonPtr()->setCountBullets(_numBullet);
		//canShoot = false;
		ammo--;		
	}	
}

void Gun::reload(){

	if (level == 1){
	
		ammo = 12;
	}
	else if (level == 2){
		ammo = 16;

	} else if(level == 3){
		ammo = 25;
	}
	else if(level == 0){
		ammo = 12;
	}
	
}