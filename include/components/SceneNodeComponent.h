#ifndef SCENENODECOMPONENT_H
#define SCENENODECOMPONENT_h

#include <Ogre.h>
#include "Component.h"

class SceneNodeComponent : Component{
public:

	SceneNodeComponent() :_sceneManager(nullptr), _sceneNode(nullptr){};
	SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position);

	~SceneNodeComponent(){
		_sceneNode->removeAndDestroyAllChildren();
		_sceneManager->destroySceneNode(_sceneNode);
	};
	

	Ogre::SceneNode* getSceneNode(){ return _sceneNode; };
	void addChild(Ogre::SceneNode* child){ _sceneNode->addChild(child); };

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _sceneNode;
};

#endif