#include "SceneNodeComponent.h"

SceneNodeComponent::SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String name, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position, Ogre::SceneNode* father){

	_sceneManager = sceneManager;

	Ogre::String enityName("SceneComponentEntity");	
	enityName.append(mesh);	
	getOgreName(enityName);


	Ogre::String nodeName("SceneComponentNode");	
	nodeName.append(mesh);
	getOgreName(nodeName);
	_entity = _sceneManager->createEntity(enityName, mesh);



	_sceneNode = _sceneManager->createSceneNode(nodeName);
	_sceneNode->attachObject(_entity);
	_sceneNode->setPosition(position);
	_sceneNode->setScale(scale);

	if (father){
		father->addChild(_sceneNode);		
	}
	else{
		_sceneManager->getRootSceneNode()->addChild(_sceneNode);
	}
}

SceneNodeComponent::~SceneNodeComponent(){

	if (_sceneNode) {
		_sceneNode->getParent()->removeChild(_sceneNode);
		_sceneNode->detachAllObjects();
		_sceneManager->destroySceneNode(_sceneNode);
		_sceneNode = nullptr;
	}
	if (_entity) {
		_sceneManager->destroyEntity(_entity);
		_entity = nullptr;
	}
	_sceneManager = nullptr;
}

void SceneNodeComponent::setMaterialName(Ogre::String materialName){
	_entity->setMaterialName(materialName);
}

void SceneNodeComponent::setMesh(Ogre::String mesh){

	Ogre::String enityName("SceneComponentEntity");
	enityName.append(Ogre::StringConverter::toString(getSceneNodeNumber()));
	enityName.append(mesh);
	getOgreName(enityName);

	_sceneNode->detachAllObjects();
	_entity = _sceneManager->createEntity(enityName, mesh);	
	_sceneNode->attachObject(_entity);
}

