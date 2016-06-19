#include "Mine.h"


Mine::Mine(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) :GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Mine", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.1,0.1,0.1));
	//_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::OBSTACLE, _sceneNodeComponent);
	addComponent(_sceneNodeComponent);
	//addComponent(_rigidBodyComponent);
	//_rigidBodyComponent->getRigidBody()->setGravity(Vector3(0,0,0));
	_player = player;
	_player->setMineActive(true);
	_player->setCountMines(_player->getCountMines()-1);
	audioController = AudioController::getSingletonPtr();
}


Mine::~Mine()
{
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}

void Mine::update(const Ogre::FrameEvent& evt){

	timer = timer + evt.timeSinceLastFrame;
	if (timer > timeExplote){
	
		shoot();
		
	}

	if (explosion){

		std::cout << "explotaaaaaaaaaaa" << std::endl;
		audioController->playAudio(Audio::MINEEXPLOSION);
		explosion = false;
		_player->setMineActive(false);
		//this->~Mine();

		//comprobar colisiones
		//si colisiones destruir
	}
}


void Mine::shoot(){

	//Activa el rigid
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::MINES, _sceneNodeComponent);
	//_rigidBodyComponent->getRigidBody()->
	addComponent(_rigidBodyComponent);

	explosion = true;

}