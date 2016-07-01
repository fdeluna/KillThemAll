#include "EnemyPathFinderComponent.h"

EnemyPathFinderComponent::EnemyPathFinderComponent(RigidBodyComponent* body) : _enemyRigidBody(body), _currentNode(nullptr){
	_pathFinder = PathFinder::getSingletonPtr();		
};

void EnemyPathFinderComponent::update(float deltaTime, Ogre::Vector3 position){

	_timer += deltaTime;
	_position = position;
	currentPath.clear();
	_pathFinder->FindPath(_enemyRigidBody->getPosition(), position, currentPath);

	if (newPath.size() > 0){
		currentPath.clear();
		currentPath = newPath;
	}

	move(deltaTime);
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
		if (_position.distance(_enemyRigidBody->getPosition()) >= 2){
			Ogre::Vector3 direction = _currentNode->getSceneNode()->getSceneNode()->getPosition() - _enemyRigidBody->getPosition();
			_enemyRigidBody->translate(direction.normalisedCopy() * deltaTime);
		}
	}
}
void EnemyPathFinderComponent::lookAt(float deltaTime){
	_enemyRigidBody->rotate(Ogre::Vector3(_position.x, 1, _position.z));
}
