#include "Mine.h"

Mine::Mine(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, GameObjectType type) :GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Mine", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
	_type = type;
	addComponent(_sceneNodeComponent);
	AudioManager = AudioManager::getSingletonPtr();
}


Mine::~Mine()
{
	if (!explosion){
		shoot();
	}
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;

	GameObject::~GameObject();
}

void Mine::update(float deltaTime){

	timer += deltaTime;

	if (timer > timeExplote || _activeMine){
		if (!explosion){
			shoot();
			timer = 0;			
		}
	}

	if (explosion && timer > timeDestroy){
		setActive(false);
		Mine::~Mine();
		timer = 0;
	}
}


void Mine::shoot(){
	explosion = true;
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::MINES, _sceneNodeComponent);
	_sceneNodeComponent->setVisible(false);
	addComponent(_rigidBodyComponent);
	AudioManager->playAudio(Audio::MINEEXPLOSION);
}