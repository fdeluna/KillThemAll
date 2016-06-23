#include "EnemyFighter.h"


void EnemyFighter::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::PLAYER){
			std::cout << "player" << std::endl;
			//audioController->playAudio(Audio::HITPLAYER);
			//_state = EnemyState::HITTED;
			_state = EnemyState::DIE;

		}
		if (gameObject->getType() == GameObjectType::BULLET){
			std::cout << "bullet" << std::endl;
			//_state = EnemyState::HITTED;
			_state = EnemyState::DIE;

		}
		if (gameObject->getType() == GameObjectType::MINES){
			std::cout << "enemigo explotaaaaa" << std::endl;
			_state = EnemyState::DIE;

		}
	}
}


void EnemyFighter::update(float deltaTime){
	if (_state == EnemyState::MOVE){
		_attackTime = 1;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
	}
	Enemy::update(deltaTime);
}


bool EnemyFighter::attack(float deltaTime){
	

	bool attack = true;
	Ogre::Vector3 attackDirecction;
	_attackTime += deltaTime;

	if (_startPositon == Ogre::Vector3::ZERO && _attackPosition == Ogre::Vector3::ZERO){
		_startPositon = getPosition();
		_attackPosition = _player->getPosition();
	}
	attackDirecction = (_attackPosition - _startPositon).normalisedCopy();
	float attackSpeed = 7;
	float backSpeed = 4;

	if (_attackTime <= 0.65){
		if (getPosition().distance(_attackPosition) > 1 && !_endAttack) {
			_rigidBodyComponent->translate(attackDirecction * attackSpeed * deltaTime);
		}
		else if (getPosition().distance(_startPositon) >= 0.25){
			_endAttack = true;
			_rigidBodyComponent->translate(-1 * attackDirecction * backSpeed * deltaTime);
		}
	}
	else{
		_attackTime = 0;
		attack = false;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
	}

	_rigidBodyComponent->rotate(Ogre::Vector3(_player->getPosition().x, 1, _player->getPosition().z));

	return attack;
}

void EnemyFighter::upgrade(){


	switch (level)
	{
	case 5:
		life = life + 4;
		speed = SPEEDS[Speed::NORMAL];
		_pathFinderComponent->setSpeed(speed);

	case 10:
		life = life + 6;
		damage = damage + 1;
		speed = SPEEDS[Speed::FAST];
		_pathFinderComponent->setSpeed(speed);

	case 15:
		life = life + 8;
		damage = damage + 2;
		_pathFinderComponent->setSpeed(speed);

	default:
		break;
	}

}