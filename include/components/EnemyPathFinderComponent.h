#ifndef ENEMYPATHFINDERCOMPONENT_H
#define ENEMYPATHFINDERCOMPONENT_H

#include "Component.h"
#include "PathFinder.h"
#include "Node.h"
#include "Player.h"
#include "RigidBodyComponent.h"

#include <future>
#include <algorithm>

class EnemyPathFinderComponent : public Component{

public:
	EnemyPathFinderComponent() : _enemyRigidBody(nullptr), _pathFinder(nullptr){ _pathFinder = PathFinder::getSingletonPtr(); };
	EnemyPathFinderComponent(RigidBodyComponent* body,Player* player);
	~EnemyPathFinderComponent(){ _player = nullptr; _enemyRigidBody = nullptr; _pathFinder = nullptr; currentPath.clear();};

	void update(float deltaTime);

	void move(float deltaTime);
	void lookAt(Ogre::Vector3 position);

private:

	float _timer = 0;
	float _speed = 5;

	Player* _player;
	RigidBodyComponent* _enemyRigidBody;
	PathFinder* _pathFinder;
	Node* _currentNode;

	std::vector<Node*> currentPath;
	std::vector<Node*> newPath;
	
	//std::future<void> newPath;

};

#endif