#include "EnemyPathFinderComponent.h"

EnemyPathFinderComponent::EnemyPathFinderComponent(RigidBodyComponent* body, Player* player) : _enemyRigidBody(body), _pathFinder(nullptr), _player(player){
	_pathFinder = PathFinder::getSingletonPtr();

	//std::async(std::launch::async, &PathFinder::FindPath, _pathFinder, _enemyRigidBody->getPosition(), _player->getPosition(), currentPath);
	//_pathFinder->FindPath(_enemyRigidBody->getPosition(), _player->getPosition(), newPath);	
	_currentNode = nullptr;
};




void EnemyPathFinderComponent::update(float deltaTime){

	_timer += deltaTime;

	if (_player){
		currentPath.clear();
		_pathFinder->FindPath(_enemyRigidBody->getPosition(), _player->getPosition(), currentPath);

		if (newPath.size() > 0){
			currentPath.clear();
			currentPath = newPath;
		}

		move(deltaTime);
	}
}


void EnemyPathFinderComponent::move(float deltaTime){

	if (currentPath.size() > 0){
		if (!_currentNode){
			_currentNode = currentPath[0];
			currentPath.erase(currentPath.begin());
		}
		if (_currentNode->getSceneNode()->getSceneNode()->getPosition().distance(_enemyRigidBody->getPosition()) <= 1){
			_currentNode = currentPath[0];
			currentPath.erase(currentPath.begin());
		}	
	}

	if (_currentNode && _enemyRigidBody){
		if (_player->getPosition().distance(_enemyRigidBody->getPosition()) >= 2){
			Ogre::Vector3 direction = _currentNode->getSceneNode()->getSceneNode()->getPosition() - _enemyRigidBody->getPosition();
			_enemyRigidBody->translate(direction.normalisedCopy() * deltaTime * 3);			
		}		
	}
}
void EnemyPathFinderComponent::lookAt(Ogre::Vector3 position){


}
