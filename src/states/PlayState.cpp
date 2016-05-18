#include "PlayState.h"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

void PlayState::enter()
{
	_root = Ogre::Root::getSingletonPtr();

	if (_root->hasSceneManager("PlayState") && _sceneMgr->hasCamera(
		"PlayState")) {
		_sceneMgr = _root->getSceneManager("PlayState");
		_camera = _sceneMgr->getCamera("PlayState");		
	}
	else {
		_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "PlayState");
		//Inicializacion de CEGUI
		_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		// set camera
		_camera = _sceneMgr->createCamera("PlayState");
	}

	createGUI();
	_exitGame = false;


	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	_camera->setNearClipDistance(5);
	_camera->setFarClipDistance(10000);
	_camera->setPosition(0,60,10);
	_camera->lookAt(0, 0, 0);

	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

	

	_mapGenerator = new MapGenerator(_sceneMgr);

	_mapGenerator->GenerateMap();

}

void PlayState::exit() {
	
	
}

void PlayState::pause() {

}

void PlayState::resume() {

}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

	_mapGenerator->update(evt.timeSinceLastFrame);

	return true;
}

bool PlayState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);


	if (_exitGame)
		return false;
	return true;
}


void PlayState::mouseMoved(const OIS::MouseEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);
}

void PlayState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));
}

void PlayState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
}

void PlayState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));

	if (OIS::KC_ESCAPE == e.key){
		_exitGame = true;
	}
}

void PlayState::keyReleased(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		static_cast<CEGUI::Key::Scan> (e.key));

}

PlayState* PlayState::getSingletonPtr()
{
	return msSingleton;
}

PlayState& PlayState::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}
CEGUI::MouseButton PlayState::convertMouseButton(OIS::MouseButtonID id)
{
	CEGUI::MouseButton ceguiId;
	switch (id) {
	case OIS::MB_Left:
		ceguiId = CEGUI::LeftButton;
		break;
	case OIS::MB_Right:
		ceguiId = CEGUI::RightButton;
		break;
	case OIS::MB_Middle:
		ceguiId = CEGUI::MiddleButton;
		break;
	default:
		ceguiId = CEGUI::LeftButton;
	}
	return ceguiId;
}


void PlayState::createGUI()
{
}