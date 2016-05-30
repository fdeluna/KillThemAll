#include "GameObject.h"


GameObject::~GameObject(){
	if (!_components.empty()){
		std::cout << _components.size() << std::endl;
		while (_components.size() > 0 ){
			Component* aux = _components.back();
			_components.pop();				
			delete aux;									
		}
		/*for (int i = 0; i < _components.size(); i++){				
			Component* aux = _components[i];
			_components.erase(_components.begin() + i);						
			delete aux;
		}*/
	}

}

void GameObject::update(float deltaTime){

	if (!_components.empty()){
		std::queue<Component*> axuQueue = _components;

		while (axuQueue.size() > 0){
			Component* aux = _components.front();			
			axuQueue.pop();
			aux->update(deltaTime);
		}
		/*for (Component* c : _components){
			c->update(deltaTime);
		}*/
	}
}


void GameObject::addComponent(Component* c){
	_components.push(c);
	//_components.push_back(c);
}

void GameObject::removeComponent(Component* c){
	//_components.erase(std::remove(_components.begin(), _components.end(),c),_components.end());
}

void GameObject::clearComponents(){
	//_components.clear();
}