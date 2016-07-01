#include "EnemyMiner.h"

void EnemyMiner::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::HELL || gameObject->getType() == GameObjectType::MINES){
			_state = EnemyState::DIE;
		}
	}
}



void EnemyMiner::update(float deltaTime){

	switch (_state)
	{
	case EnemyState::MOVE:
		if (_targetPosition == Ogre::Vector3::ZERO){
			_targetPosition = _map->getRandomNodePosition();
		}

		if (_targetPosition.distance(getPosition()) <= 2){
			Ogre::Vector3 aux = _map->getRandomNodePosition();
			while (_targetPosition.distance(aux) < 5){
				aux = _map->getRandomNodePosition();
			}
			_targetPosition = aux;
			_state = EnemyState::ATTACK;
		}
		break;
	case EnemyState::DIE:
		if (_mine){
			_mine->shoot();
			delete _mine;
			_mine = nullptr;
		}
		break;
	}


	if (_mine && _mine->isActive()){
		_mine->update(deltaTime);
	}
	else{
		_mine = nullptr;
	}

	Enemy::update(deltaTime);
}


void EnemyMiner::move(float deltaTime){
	if (_pathFinderComponent){
		_pathFinderComponent->update(deltaTime * _speed, _targetPosition);
	}
}

bool EnemyMiner::attack(float deltaTime){

	if (!_mine){
		Ogre::Vector3 positionMine = Ogre::Vector3(getPosition());
		_mine = new Mine(_sceneManager, Ogre::Vector3(positionMine.x, 0.5, positionMine.z), MESHES[MeshName::MINE], GameObjectType::MINEENEMY);
	}
	_state = EnemyState::MOVE;
	return true;
}