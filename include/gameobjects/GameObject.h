#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Enum.h"

#include <Ogre.h>
#include <iostream>
#include <vector>
#include <algorithm>

class Component;

class GameObject{
public:

	GameObject(): _sceneManager(nullptr){};
	GameObject(Ogre::SceneManager* sceneManager) : _sceneManager(sceneManager){};

	virtual ~GameObject(){ _components.clear(); };

	virtual void update(float deltaTime);

	virtual void collision(GameObject* gameObject){};
	void addComponent(Component* c);
	void removeComponent(Component* c);
	void clearComponents();
	GameObjectType getType(){ return _type; };

	bool isActive(){ return _active; };
	void setActive(bool active){ _active = active; };
	

protected:

	Ogre::SceneManager* _sceneManager;
	bool _active = true;		
	std::vector<Component*> _components;
	GameObjectType _type;


};
#endif