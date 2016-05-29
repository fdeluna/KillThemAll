#include "SceneNodeComponent.h"


SceneNodeComponent::SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position){
	
	_sceneManager = sceneManager;

	Ogre::String enityName("SceneComponentEntity");
	enityName.append(Ogre::StringConverter::toString(getSceneNodeNumber()));
	enityName.append(mesh);

	Ogre::String nodeName("SceneComponentNode");
	nodeName.append(Ogre::StringConverter::toString(getSceneNodeNumber()));
	nodeName.append(mesh);

	Ogre::Entity* entity = _sceneManager->createEntity(enityName, mesh);
	_sceneNode = _sceneManager->createSceneNode(nodeName);

	_sceneNode->attachObject(entity);
	_sceneNode->setPosition(position);
	_sceneNode->setScale(scale);	

	_sceneManager->getRootSceneNode()->addChild(_sceneNode);
		

}