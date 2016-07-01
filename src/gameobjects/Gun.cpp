#include "Gun.h"


Gun::Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{
	_sceneNodeComponentGun = new SceneNodeComponent(_sceneManager, "Gun", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position, player->getSceneNodeComponent()->getSceneNode());
	_sceneNodeComponentGun->getSceneNode()->setScale(Ogre::Vector3(4, 4, 4));
	_rigidBodyComponentGun = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponentGun);
	addComponent(_sceneNodeComponentGun);	
	_player = player;
	_AudioManager = AudioManager::getSingletonPtr();
}


Gun::~Gun()
{
	delete _rigidBodyComponentGun;
	delete _sceneNodeComponentGun;
	Gun::~Gun();
}

void Gun::update(const Ogre::FrameEvent& evt){

}

void Gun::upgrade(){
	_level++;
	switch (_level)
	{
	case 2:
		_velAtack = ATTACKVELOCITIES[AttackVelocity::NORMAL];		
		_ammo = 16;
		break;

	case 3:
		_velAtack = ATTACKVELOCITIES[AttackVelocity::FAST];		
		_ammo = 25;		
		break;	
	}

}
void Gun::shoot(){

	if (_canShoot && _ammo > 0 && !_reloading){
		_AudioManager->playAudio(Audio::SHOOT);

		Ogre::Vector3 mousePosition(_player->getPlayerInputComponent()->getMousePositionWeapon());
		Ogre::Vector3 playerPosition(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x, 1, _player->getSceneNodeComponent()->getSceneNode()->getPosition().z);

		Ogre::Vector3 direction = mousePosition - playerPosition;
		Ogre::Vector3 directionShoot = direction.normalisedCopy();

		Bullet* bullet = new Bullet(_sceneNodeComponentGun->getSceneManager(), playerPosition, MESHES[MeshName::BULLETP]);
		bullet->getSceneNodeComponent()->getSceneNode()->setScale(Ogre::Vector3(0.2, 0.2, 0.2));
		bullet->getRigidBodyComponent()->getRigidBody()->setLinearVelocity(directionShoot * _velAtack);
		bullet->getRigidBodyComponent()->getRigidBody()->setGravity(Ogre::Vector3(0, 0, 0));
		bullet->getRigidBodyComponent()->rotate(mousePosition);

		_numBullet++;
		WaveManager::getSingletonPtr()->setBulletUsed(WaveManager::getSingletonPtr()->getBulletsUsed() + _numBullet);
		_ammo--;
	}
}

void Gun::reload(){

	if (_level <= 1){
		_ammo = 12;
	}
	else if (_level == 2){
		_ammo = 16;

	}
	else if (_level == 3){
		_ammo = 25;
	}
}