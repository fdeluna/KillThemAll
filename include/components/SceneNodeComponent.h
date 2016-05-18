#ifndef SCENENODECOMPONENT_H
#define SCENENODECOMPONENT_h

#include "Component.h"
#include "Enum.h"

#include <Ogre.h>

class SceneNodeComponent : public Component{
public:

	SceneNodeComponent() :_sceneManager(nullptr), _sceneNode(nullptr),_entity(nullptr){};
	SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position);

	~SceneNodeComponent(){
		_sceneNode->removeAndDestroyAllChildren();
		_sceneManager->destroySceneNode(_sceneNode);
	};
	

	Ogre::SceneNode* getSceneNode(){ return _sceneNode; };
	Ogre::Entity* getEntity(){ return _entity; };

	void addChild(Ogre::SceneNode* child){ _sceneNode->addChild(child); };
	void setDiffuseColor(Ogre::ColourValue diffuseColor);
	void addToRootScene();

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _sceneNode;
	Ogre::Entity* _entity;
};

#endif