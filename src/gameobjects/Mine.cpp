#include "Mine.h"

Mine::Mine(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, GameObjectType type) :GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Mine", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
	_type = type;
	addComponent(_sceneNodeComponent);	
	audioController = AudioController::getSingletonPtr();
}


Mine::~Mine()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	//delete audioController;
	GameObject::~GameObject();
}

void Mine::update(float deltaTime){

	timer += deltaTime;

	if (timer > timeExplote || _activeMine){
		if (!explosion){		
			shoot();
			timer = 0;
			explosion = true;
		}
	}

	if (explosion && timer > timeDestroy){
		setActive(false);
		Mine::~Mine();
		timer = 0;
	}
}


void Mine::shoot(){
	//Activa el rigid	
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::MINES, _sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	audioController->playAudio(Audio::MINEEXPLOSION);
}