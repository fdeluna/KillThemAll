#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent(RigidBodyComponent* body, Ogre::SceneManager* sceneManager) : _playerBody(body), _sceneManager(sceneManager), _inputManager(InputManager::getSingletonPtr())
{
	_camera = _sceneManager->getCamera("PlayState");
}

void PlayerInputComponent::update(float deltaTime){

	_camera->setPosition(_playerBody->getPosition().x, 12.5, _playerBody->getPosition().z - 4);
	move(deltaTime);
	lookAt();
}


void PlayerInputComponent::move(float deltaTime){

	Ogre::Vector3 vectorDirection = Ogre::Vector3::ZERO;

	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_W)) vectorDirection += Ogre::Vector3(0, 0, 1);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_S)) vectorDirection += Ogre::Vector3(0, 0, -1);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_A)) vectorDirection += Ogre::Vector3(1, 0, 0);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_D)) vectorDirection += Ogre::Vector3(-1, 0, 0);

	_playerBody->translate(vectorDirection * _speed * deltaTime);

}

void PlayerInputComponent::lookAt(){

	OIS::MouseState e = _inputManager->getMouse()->getMouseState();

	float x = e.X.abs / (float)Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->getWidth();
	float y = e.Y.abs / (float)Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->getHeight();

	Ogre::Vector3 mousePosition = PhysicsManager::getSingletonPtr()->getMouseWorldPosition(x, y);
	positionMouseForWaeapon = Ogre::Vector3(mousePosition.x, 1, mousePosition.z);

	_playerBody->rotate(Ogre::Vector3(mousePosition.x, 1, mousePosition.z));
}