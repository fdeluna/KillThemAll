#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"

#include <Ogre.h>
#include <iostream>
#include <vector>
#include <algorithm>

class Component;

class GameObject{
public:

	GameObject(): _sceneManager(nullptr){};
	GameObject(Ogre::SceneManager* sceneManager) : _sceneManager(sceneManager){};

	~GameObject();

	virtual void update(float deltaTime);

	void addComponent(Component* c);
	void removeComponent(Component* c);
	void clearComponents();

	bool isActive(){ return _active; };
	void setActive(bool active){ _active = active; };

protected:

	Ogre::SceneManager* _sceneManager;

	bool _active;	
	
	std::vector<Component*> _components;

};
#endif