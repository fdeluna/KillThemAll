#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

class GameObject;

class Component
{
public:
	Component() : _gameObject(nullptr){};
	Component(GameObject* gameObject) : _gameObject(gameObject){};

	~Component(){ _gameObject = nullptr; };

	virtual void update(float deltaTime){};
	

private:
	GameObject* _gameObject;
};

#endif