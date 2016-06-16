#include "EnemyFighter.h"


void EnemyFighter::collision(GameObject* gameObject){
	if (gameObject->getType() == GameObjectType::PLAYER){
		_state = EnemyState::DIE;
	}	
}