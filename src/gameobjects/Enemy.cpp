#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player, int level, GameObjectType type) : GameObject(sceneManager), _player(player), _level(level){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Enemy", mesh, Ogre::Vector3(0.1, 0.25, 0.1), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, type, _sceneNodeComponent);
	_pathFinderComponent = new EnemyPathFinderComponent(_rigidBodyComponent);
	_state = EnemyState::MOVE;
	_type = type;
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	_audioManager = AudioManager::getSingletonPtr();
	_audioManager->playAudio(Audio::SPAWN);

	nodeParticleHitEnemy = sceneManager->createSceneNode("NodeParticulaHitEnemy" + _sceneNodeComponent->getEntity()->getName());

	
	_sceneNodeComponent->getSceneNode()->addChild(nodeParticleHitEnemy);		
	nodeParticleHitEnemy->setScale(0.01, 0.01, 0.01);
	partSystem2 = sceneManager->createParticleSystem("HitEnemy" + _sceneNodeComponent->getEntity()->getName(), "Sangre2");
	nodeParticleHitEnemy->attachObject(partSystem2);	
	partSystem2->setVisible(false);
}

Enemy::~Enemy(){

	delete _pathFinderComponent;
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}


void Enemy::update(float deltaTime){

	partSystem2->_update(deltaTime);	

	switch (_state)
	{			
	case EnemyState::MOVE:
		move(deltaTime);
		break;
	case EnemyState::ATTACK:
		attack(deltaTime);
		break;
	case EnemyState::DIE:
		timerParticle += deltaTime;

		if (timerParticle < 0.2){
			partSystem2->setVisible(true);

		}
		else{
			_audioManager->playAudio(Audio::KILLENEMY);

			_active = false;
			
		}
		break;	
	}
	GameObject::update(deltaTime);
}

bool Enemy::attackDistance(){
	return _player->getPosition().distance(_rigidBodyComponent->getPosition()) <= 2;
}