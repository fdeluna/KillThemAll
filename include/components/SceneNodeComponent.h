#ifndef SCENENODECOMPONENT_H
#define SCENENODECOMPONENT_h

#include "Component.h"
#include "Enum.h"

#include <Ogre.h>

class SceneNodeComponent : public Component{
public:

	SceneNodeComponent() :_sceneManager(nullptr), _sceneNode(nullptr),_entity(nullptr){};
	SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String name,Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position);

	~SceneNodeComponent(){
		_sceneNode->removeAndDestroyAllChildren();
		_sceneManager->destroySceneNode(_sceneNode);
	};		

	void setPosition(Ogre::Vector3 position){ _sceneNode->setPosition(position); };
	Ogre::Vector3 getPosition(){ return _sceneNode->getPosition(); };;
	void setScale(Ogre::Vector3 scale){ _sceneNode->setScale(scale); };
	Ogre::Vector3 getScale(){ return _sceneNode->getScale(); };



	void addChild(Ogre::SceneNode* child){ _sceneNode->addChild(child); };
	void setDiffuseColor(Ogre::ColourValue diffuseColor);
	void addToRootScene();
	void setMaterialName(Ogre::String materialName);
	
	

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _sceneNode;
	Ogre::Entity* _entity;
};

#endif