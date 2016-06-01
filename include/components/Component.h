#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

#include <iostream>

class GameObject;

class Component
{
public:
	Component() : _gameObject(nullptr){};
	Component(GameObject* gameObject) : _gameObject(gameObject){};

	~Component(){ _gameObject = nullptr; };

	virtual void update(float deltaTime){};	

	virtual void getName(){ std::cout << " COMPONENT" << std::endl; };
	

private:
	GameObject* _gameObject;
};

#endif