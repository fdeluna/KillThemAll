#ifndef GameState_H
#define GameState_H

#include "GameManager.h"
#include "InputManager.h"

#include <Ogre.h>
#include <OIS/OIS.h>

class GameState {

public:
	GameState() {};
	
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	
	virtual void keyPressed(const OIS::KeyEvent &e) = 0;
	virtual void keyReleased(const OIS::KeyEvent &e) = 0;

	virtual void mouseMoved(const OIS::MouseEvent &e) = 0;
	virtual void mousePressed(const OIS::MouseEvent &e,
		OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent &e,
		OIS::MouseButtonID id) = 0;
	
	virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
	virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;
	
	void changeState(GameState* state) {
		GameManager::getSingletonPtr()->changeState(state);
	}
	void pushState(GameState* state) {
		GameManager::getSingletonPtr()->pushState(state);
	}
	void popState() {
		GameManager::getSingletonPtr()->popState();
	}

};

#endif
