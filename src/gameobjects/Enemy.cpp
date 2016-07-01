#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player, int level, GameObjectType type) : GameObject(sceneManager), _player(player), _level(level){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Enemy", mesh, Ogre::Vector3(0.1, 0.25, 0.1), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, type, _sceneNodeComponent);
	_pathFinderComponent = new EnemyPathFinderComponent(_rigidBodyComponent);
	_state = EnemyState::MOVE;
	_type = type;
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	audioController = AudioController::getSingletonPtr();
	audioController->playAudio(Audio::SPAWN);
}

Enemy::~Enemy(){

	delete _pathFinderComponent;
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}


void Enemy::update(float deltaTime){

	switch (_state)
	{			
	case EnemyState::MOVE:
		move(deltaTime);
		break;
	case EnemyState::ATTACK:
		attack(deltaTime);
		break;
	case EnemyState::DIE:
		audioController->playAudio(Audio::KILLENEMY);
		_active = false;		
		break;	
	}
	GameObject::update(deltaTime);
}

bool Enemy::attackDistance(){
	return _player->getPosition().distance(_rigidBodyComponent->getPosition()) <= 2;
}