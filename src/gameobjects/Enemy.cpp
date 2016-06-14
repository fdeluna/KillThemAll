#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player) : GameObject(sceneManager){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Enemy", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::ENEMY, _sceneNodeComponent);
	_pathFinderComponent = new EnemyPathFinderComponent(_rigidBodyComponent,player);
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	addComponent(_pathFinderComponent);
}

Enemy::~Enemy(){
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	delete _pathFinderComponent;
	GameObject::~GameObject();
}