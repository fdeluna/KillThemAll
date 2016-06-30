#include "EnemyMiner.h"

void EnemyMiner::collision(GameObject* gameObject){
	if (gameObject){

		if (gameObject->getType() == GameObjectType::HELL){
			_life = 0;
		}

		if (gameObject->getType() == GameObjectType::MINES){
			_state = EnemyState::DIE;
		}
	}
}



void EnemyMiner::update(float deltaTime){
	std::cout << _targetPosition.distance(getPosition()) << std::endl;

	// TODO  COGER UNA POSICIÓN MAS ALEJADA
	if (_targetPosition == Ogre::Vector3::ZERO){		
		_targetPosition = _map->getRandomNodePosition();
	}

	if (_targetPosition.distance(getPosition()) <= 2){
		_targetPosition = _map->getRandomNodePosition();
		_state = EnemyState::ATTACK;
	}

	// TODO SWITCH DE ESTADOS
	if (_state == EnemyState::ATTACK){
		attack(deltaTime);
		_state = EnemyState::MOVE;
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

	Ogre::Vector3 positionMine = Ogre::Vector3(getPosition());
	_mine = new Mine(_sceneManager, Ogre::Vector3(positionMine.x, 0.5, positionMine.z), MESHES[MeshName::MINE]);

	return true;
}