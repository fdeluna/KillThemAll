#include "GameObject.h"


GameObject::~GameObject(){
	if (!_components.empty()){

		for (int i = 0; i < _components.size(); i++){				
			Component* aux = _components[i];
			_components.erase(_components.begin() + i);
			delete aux;
		}
	}

}

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