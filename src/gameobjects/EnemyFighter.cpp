#include "EnemyFighter.h"

void EnemyFighter::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::PLAYER){

			if (isAttacking && _nextAttack < 0.65){
				_player->hitted(_damage);
				_nextAttack = 0;
				isAttacking = false;
			}

		}

		if (gameObject->getType() == GameObjectType::HELL || gameObject->getType() == GameObjectType::MINES){
			_state = EnemyState::DIE;
		}
	}
}

void EnemyFighter::update(float deltaTime){
	switch (_state)
	{
	case EnemyState::MOVE:
		_attackTime = 1;
		_nextAttack = 0;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
		move(deltaTime);
		if (attackDistance()){
			_state = EnemyState::ATTACK;
		}
		break;
	case EnemyState::ATTACK:
		_nextAttack += deltaTime;
		if (!attackDistance() & !attack(deltaTime)){
			_state = EnemyState::MOVE;
		}
		break;
	}
	_rigidBodyComponent->rotate(Ogre::Vector3(_player->getPosition().x, 1, _player->getPosition().z));
	Enemy::update(deltaTime);
}


void EnemyFighter::move(float deltaTime){
	if (_pathFinderComponent){
		_pathFinderComponent->update(deltaTime * _speed, _player->getPosition());
	}
}

bool EnemyFighter::attack(float deltaTime){

	bool attack = true;
	Ogre::Vector3 attackDirecction;
	_attackTime += deltaTime;

	if (_startPositon == Ogre::Vector3::ZERO && _attackPosition == Ogre::Vector3::ZERO){
		_startPositon = getPosition();
		_attackPosition = _player->getPosition();
		isAttacking = true;
	}
	attackDirecction = (_attackPosition - _startPositon).normalisedCopy();

	if (_attackTime <= 0.8){
		if (getPosition().distance(_attackPosition) > 1 && !_endAttack) {
			_rigidBodyComponent->translate(attackDirecction * _attackSpeed * deltaTime);
		}
		else if (getPosition().distance(_startPositon) >= 0.1){
			isAttacking = false;
			_endAttack = true;
			_rigidBodyComponent->translate(-1 * attackDirecction * _backSpeed * deltaTime);
		}
	}
	else{
		_attackTime = 0;
		_nextAttack = 0;
		attack = false;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
	}

	return attack;
}

