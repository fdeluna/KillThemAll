#include "PlayerInputComponent.h"

void PlayerInputComponent::update(float deltaTime){

	move(deltaTime);
	lookAt(deltaTime);
}


void PlayerInputComponent::move(float deltaTime){

	Ogre::Vector3 vectorDirection = Ogre::Vector3::ZERO;
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_W)) vectorDirection += Ogre::Vector3(0, 0, 1);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_S)) vectorDirection += Ogre::Vector3(0, 0, -1);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_A)) vectorDirection += Ogre::Vector3(1, 0, 0);
	if (_inputManager->getKeyboard()->isKeyDown(OIS::KC_D)) vectorDirection += Ogre::Vector3(-1, 0, 0);

	_playerBody->translate(vectorDirection * _speed * deltaTime);


}

void PlayerInputComponent::lookAt(float deltaTime){

	OIS::MouseState e = _inputManager->getMouse()->getMouseState();

	float x = e.X.abs / (float)Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->getWidth();
	float y = e.Y.abs / (float)Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->getHeight();

	Ogre::Vector3 mousePosition = PhysicsManager::getSingletonPtr()->getMouseWorldPosition(x, y);
	
	_playerBody->rotate(Ogre::Vector3(mousePosition.x, 1 , mousePosition.z));


	// TODO SEGUIR POR AQUÍ MAÑANA
	/*Ogre::Vector3 lookAt();
	_inputManager->getMouse()->getMouseState().X.
	std::cout << "MOUSE X " << _inputManager->getMouse()->getMouseState().X.rel << std::endl;
	std::cout << "MOUSE Y " << _inputManager->getMouse()->getMouseState().Y.rel << std::endl;*/

}