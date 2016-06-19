#include "EnemyFighter.h"


void EnemyFighter::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::PLAYER){			
			if (isAttacking && _nextAttack >= 0.65){
				_player->hitted(1);
				_nextAttack = 0;
			}
			//_state = EnemyState::DIE;
		}
	}
}


void EnemyFighter::update(float deltaTime){
	if (_state == EnemyState::MOVE){
		_attackTime = 1;
		_nextAttack = 1;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
	}
	else{
		_nextAttack += deltaTime;
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

	if (_attackTime <= 0.8){
		if (getPosition().distance(_attackPosition) > 1 && !_endAttack) {
			_rigidBodyComponent->translate(attackDirecction * attackSpeed * deltaTime);
			isAttacking = true;
		}
		else if (getPosition().distance(_startPositon) >= 0.25){
			_endAttack = true;
			_rigidBodyComponent->translate(-1 * attackDirecction * backSpeed * deltaTime);
			isAttacking = false;
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