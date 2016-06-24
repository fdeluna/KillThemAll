#include "Mine.h"


Mine::Mine(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Mine", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.1,0.1,0.1));
	
//_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponent);
	addComponent(_sceneNodeComponent);
	_type = GameObjectType::MINES;

	//addComponent(_rigidBodyComponent);
	//_rigidBodyComponent->getRigidBody()->setGravity(Vector3(0,0,0));
	_player = player;
	_player->setMineActive(true);
	_player->setCountMines(_player->getCountMines()-1);
	audioController = AudioController::getSingletonPtr();
	automaticExplosion = false;

	/*
	nodeParticle = sceneManager->createSceneNode("NodeParticula2");
	nodeParticle->setScale(0.03, 0.03, 0.03);
	_sceneNodeComponent->getSceneNode()->addChild(nodeParticle);
	nodeParticle->setPosition(_sceneNodeComponent->getSceneNode()->getPosition());
	partSystem = sceneManager->createParticleSystem("Shoot", "Shoot2");
	nodeParticle->attachObject(partSystem);
	partSystem->setVisible(true);
	*/
}


Mine::~Mine()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	//delete audioController;
	GameObject::~GameObject();
}

void Mine::collision(GameObject* gameObject){
	if (gameObject){
		if (gameObject->getType() == GameObjectType::ENEMY){
			gameObject->setActive(false);
			std::cout << "enemigo explotaaaaa" << std::endl;
		}
		
	}
}


void Mine::update(const Ogre::FrameEvent& evt){

	timer = timer + evt.timeSinceLastFrame;

	//partSystem->_update(evt.timeSinceLastFrame*4.0);

	if (timer >timeDestroy){
		setActive(false);
		Mine::~Mine();
		timer = 0;
		_player->setMineActive(false);

	}
	if (((timer > timeExplote || automaticExplosion) && _player->getMineActive()) && explosion){
	
		
		if (!automaticExplosion){
			shoot();
		}
		std::cout << "explotaaaaaaaaaaa" << std::endl;
		explosion = false;
		timeDestroy = timer + 1;
	}

	if (explosion){
		
		
		
	
	}
}


void Mine::shoot(){

	//Activa el rigid
	//_rigidBodyComponent->getRigidBody()->
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::MINES, _sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	audioController->playAudio(Audio::MINEEXPLOSION);
	explosion = true;

}