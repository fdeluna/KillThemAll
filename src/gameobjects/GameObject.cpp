#include "GameObject.h"


void GameObject::update(float deltaTime){

	if (!_components.empty()){
		for (Component* c : _components){
			c->update(deltaTime);
		}
	}
}


void GameObject::addComponent(Component* c){	
	_components.push_back(c);
}

void GameObject::removeComponent(Component* c){
	_components.erase(std::remove(_components.begin(), _components.end(),c),_components.end());
}

void GameObject::clearComponents(){
	_components.clear();
}