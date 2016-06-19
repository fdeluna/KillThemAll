#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player) : GameObject(sceneManager){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Enemy", mesh, Ogre::Vector3(0.1, 0.25, 0.1), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::ENEMY, _sceneNodeComponent);
	_pathFinderComponent = new EnemyPathFinderComponent(_rigidBodyComponent, player);
	_player = player;
	_state = EnemyState::MOVE;
	_type = GameObjectType::ENEMY;
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	//addComponent(_pathFinderComponent);
}


void Enemy::update(float deltaTime){

	switch (_state)
	{

	case EnemyState::ATTACK:
		if (!attackDistance() & !attack(deltaTime)){
			_state = EnemyState::MOVE;
		}
		break;
	case EnemyState::MOVE:
		move(deltaTime);
		if (attackDistance()){
			_state = EnemyState::ATTACK;
		}
		break;
	case EnemyState::DIE:
		_active = false;
		die(deltaTime);
		break;
	case EnemyState::HITTED:
		hitted(deltaTime);
		break;
	default:
		break;
	}

	GameObject::update(deltaTime);
}

bool Enemy::attackDistance(){
	return _player->getPosition().distance(_rigidBodyComponent->getPosition()) <= 2;
}

void Enemy::move(float deltaTime){
	_pathFinderComponent->update(deltaTime);
}

Enemy::~Enemy(){
	
	delete _pathFinderComponent;
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}