#include "Gun.h"


Gun::Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{
	_sceneNodeComponentGun = new SceneNodeComponent(_sceneManager, "Gun", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position, player->getSceneNodeComponent()->getSceneNode());
	_sceneNodeComponentGun->getSceneNode()->setScale(Ogre::Vector3(4, 4, 4));
	_rigidBodyComponentGun = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponentGun);
	addComponent(_sceneNodeComponentGun);
	_player = player;
	_audioManager = AudioManager::getSingletonPtr();

	nodeParticle = sceneManager->createSceneNode("NodeParticula");
	nodeParticle->setScale(0.03, 0.03, 0.03);
	_sceneNodeComponentGun->getSceneNode()->addChild(nodeParticle);
	nodeParticle->setPosition(Ogre::Vector3(5, 0, -0.5));
	partSystem = sceneManager->createParticleSystem("Shoot", "Shoot2");
	nodeParticle->attachObject(partSystem);
	partSystem->setVisible(false);
}


Gun::~Gun()
{

	if (_bullets.size() > 0){
		for (int i = 0; i < _bullets.size(); i++){

			Bullet* aux = _bullets[i];
			_bullets.erase(_bullets.begin() + i);
			delete aux;
		}
	}
	_bullets.clear();
	delete _rigidBodyComponentGun;
	delete _sceneNodeComponentGun;
	Gun::~Gun();
}

void Gun::update(float deltaTime){
	partSystem->_update(deltaTime);
	timeParticle += deltaTime;
	if (timeParticle < 0.2){
		partSystem->setVisible(true);

	}
	else{
		partSystem->setVisible(false);

	}

	if (_bullets.size() > 0){
		for (int i = 0; i < _bullets.size(); i++){
			if (_bullets[i]->isActive()){
				_bullets[i]->update(deltaTime);
			}
			else{
				Bullet* aux = _bullets[i];
				_bullets.erase(_bullets.begin() + i);
				delete aux;
			}
		}
	}
}

void Gun::upgrade(){

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
		_audioManager->playAudio(Audio::SHOOT);
		timeParticle = 0;

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
		_bullets.push_back(bullet);
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