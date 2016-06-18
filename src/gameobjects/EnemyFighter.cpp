#include "EnemyFighter.h"


void EnemyFighter::collision(GameObject* gameObject){
	/*if (gameObject->getType() == GameObjectType::PLAYER){
		_state = EnemyState::DIE;
		}*/
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

	return attack;
}