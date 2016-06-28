#ifndef ENEMYPATHFINDERCOMPONENT_H
#define ENEMYPATHFINDERCOMPONENT_H

#include "Component.h"
#include "MapNode.h"
#include "PathFinder.h"
#include "Player.h"
#include "RigidBodyComponent.h"

class EnemyPathFinderComponent : public Component{

public:
	EnemyPathFinderComponent() : _enemyRigidBody(nullptr), _pathFinder(nullptr){ _pathFinder = PathFinder::getSingletonPtr(); };
	EnemyPathFinderComponent(RigidBodyComponent* body);
	~EnemyPathFinderComponent(){currentPath.clear();};

	void update(float deltaTime, Ogre::Vector3 position);

	void move(float deltaTime);
	void lookAt(float deltaTime);
	void setSpeed(float speed){ _speed = speed; };

private:

	float _timer = 0;
	float _speed = SPEEDS[Speed::SLOW];
	bool attackDistance = false;
	
	Ogre::Vector3 _position;
	RigidBodyComponent* _enemyRigidBody;
	PathFinder* _pathFinder;
	MapNode* _currentNode;

	std::vector<MapNode*> currentPath;
	std::vector<MapNode*> newPath;

};

#endif