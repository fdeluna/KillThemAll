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

		if (gameObject->getType() == GameObjectType::HELL){		
				_life = 0;
		}
		
		if (gameObject->getType() == GameObjectType::MINES){			
			_state = EnemyState::DIE;
		}
	}
}



void EnemyFighter::update(float deltaTime){
	if (_state == EnemyState::MOVE){
		_attackTime = 1;
		_nextAttack = 0;
		_endAttack = false;
		_startPositon = Ogre::Vector3::ZERO;
		_attackPosition = Ogre::Vector3::ZERO;
		// TODO CAMBIAR DE SITIO
		//AudioController::getSingletonPtr()->playAudio(Audio::HITENEMY);
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
		isAttacking = true;
	}
	attackDirecction = (_attackPosition - _startPositon).normalisedCopy();

	if (_attackTime <= 0.8){
		if (getPosition().distance(_attackPosition) > 1 && !_endAttack) {
			_rigidBodyComponent->translate(attackDirecction * _attackSpeed * deltaTime);									
			_sceneNodeComponent->setMaterialName("CuerpoEnemyFigtherAttakking");
		}
		else if (getPosition().distance(_startPositon) >= 0.1){
			isAttacking = false;
			_endAttack = true;
			_rigidBodyComponent->translate(-1 * attackDirecction * _backSpeed * deltaTime);			
			_sceneNodeComponent->setMaterialName("CuerpoEnemyFigther");

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

	_rigidBodyComponent->rotate(Ogre::Vector3(_player->getPosition().x, 1, _player->getPosition().z));


	return attack;
}

