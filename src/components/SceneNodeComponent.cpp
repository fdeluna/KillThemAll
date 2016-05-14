#include "SceneNodeComponent.h"

SceneNodeComponent::SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position){

	Ogre::Root* root = Ogre::Root::getSingletonPtr();
	_sceneManager = sceneManager;

	Ogre::Entity* entity = _sceneManager->createEntity(mesh.append("SceneComponent"), mesh);
	_sceneNode->attachObject(entity);
	_sceneNode->setPosition(position);
	_sceneNode->setScale(scale);
}