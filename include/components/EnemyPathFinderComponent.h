#ifndef ENEMYPATHFINDERCOMPONENT_H
#define ENEMYPATHFINDERCOMPONENT_H

#include "Component.h"
#include "PathFinder.h"
#include "Node.h"
#include "Player.h"
#include "RigidBodyComponent.h"

class EnemyPathFinderComponent : public Component{

public:
	EnemyPathFinderComponent() : _enemyRigidBody(nullptr), _pathFinder(nullptr){ _pathFinder = PathFinder::getSingletonPtr(); };
	EnemyPathFinderComponent(RigidBodyComponent* body,Player* player);
	~EnemyPathFinderComponent(){currentPath.clear();};

	void update(float deltaTime);

	void move(float deltaTime);
	void lookAt(Ogre::Vector3 position);

private:

	float _timer = 0;
	float _speed = 5;
	bool attackDistance = false;

	Player* _player;
	RigidBodyComponent* _enemyRigidBody;
	PathFinder* _pathFinder;
	Node* _currentNode;

	std::vector<Node*> currentPath;
	std::vector<Node*> newPath;		

};

#endif