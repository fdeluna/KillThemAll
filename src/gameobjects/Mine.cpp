#include "Mine.h"

Mine::Mine(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, GameObjectType type) :GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Mine", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
	_type = type;
	addComponent(_sceneNodeComponent);
	_audioManager = AudioManager::getSingletonPtr();
		
	nodeParticle = sceneManager->createSceneNode("NodeParticulaMine2" + _sceneNodeComponent->getEntity()->getName());
	nodeParticle->setScale(0.01, 0.01, 0.01);
	_sceneNodeComponent->getSceneNode()->addChild(nodeParticle);		
	partSystem = sceneManager->createParticleSystem("Mine" + _sceneNodeComponent->getEntity()->getName(), "Mine");
	nodeParticle->attachObject(partSystem);
	partSystem->setVisible(false);
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
	
	partSystem->_update(deltaTime*5.0);	

	if (timer > timeExplote || _activeMine){
		partSystem->setVisible(true);

		if (!explosion){
			shoot();
			timer = 0;			
		}
	}

	if (explosion && timer > timeDestroy){
		partSystem->setVisible(true);
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
	_audioManager->playAudio(Audio::MINEEXPLOSION);
	partSystem->setVisible(true);

}