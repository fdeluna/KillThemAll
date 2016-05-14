#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Component;

class GameObject{
public:

	GameObject(){};

	~GameObject(){		
	};

	virtual void update(float deltaTime);

	void addComponent(Component* c);
	void removeComponent(Component* c);
	void clearComponents();

	bool isActive(){ return _active; };
	void setActive(bool active){ _active = active; };

private:

	bool _active;

	std::vector<Component*> _components;

};
#endif