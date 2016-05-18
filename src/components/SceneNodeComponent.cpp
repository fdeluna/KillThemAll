#include "SceneNodeComponent.h"


SceneNodeComponent::SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position){

	_sceneManager = sceneManager;

	Ogre::String enityName("SceneComponentEntity");
	enityName.append(Ogre::StringConverter::toString(getSceneNodeNumber()));
	enityName.append(mesh);

	Ogre::String nodeName("SceneComponentNode");
	nodeName.append(Ogre::StringConverter::toString(getSceneNodeNumber()));
	nodeName.append(mesh);

	_entity = _sceneManager->createEntity(enityName, mesh);

	
	_sceneNode = _sceneManager->createSceneNode(nodeName);
	_sceneNode->attachObject(_entity);

	_sceneNode->setPosition(position);
	_sceneNode->setScale(scale);

	
	_sceneManager->getRootSceneNode()->addChild(_sceneNode);
}

void SceneNodeComponent::setDiffuseColor(Ogre::ColourValue diffuseColor){
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("ObstacleMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
	Ogre::Pass *pass = material->getTechnique(0)->getPass(0);
	pass->setAmbient(diffuseColor);
	_entity->setMaterial(material);
}

void SceneNodeComponent::addToRootScene(){
	_sceneManager->getRootSceneNode()->addChild(_sceneNode);
}