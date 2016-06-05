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
		//_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		// set camera
		_camera = _sceneMgr->createCamera("PlayState");
	}

	createGUI();
	_exitGame = false;

	// TODO LIGHTS
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	// TODO REFACTOR TO INIT WAVE
	_camera->setPosition(Ogre::Vector3(0, 20, 15));
	_camera->lookAt(Ogre::Vector3(0, 0, 0));
	_camera->setNearClipDistance(1);
	_camera->setFarClipDistance(10000);

	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);		
	_viewport->setBackgroundColour(Ogre::ColourValue(0.18, 0.31, 0.31));

	double width = _viewport->getActualWidth();
	double height = _viewport->getActualHeight();
	_camera->setAspectRatio(width / height);

	_physicsManager = new PhysicsManager(_sceneMgr, true);
	_mapGenerator = new MapGenerator(_sceneMgr);	


}

void PlayState::exit() {
	_mapGenerator->cleanMap();
	delete _mapGenerator;
	delete _physicsManager;

	_sceneMgr->clearScene();
	
}

void PlayState::pause() {

}

void PlayState::resume() {

}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

	_deltaT = evt.timeSinceLastFrame;

	_physicsManager->updatePhysics(_deltaT);
	//_mapGenerator->update(_deltaT);

	Ogre::Vector3 vt(0, 0, 0);     Ogre::Real tSpeed = 20.0;

	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_ESCAPE)) return false;
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_UP))    vt += Ogre::Vector3(0, 0, -1);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_DOWN))  vt += Ogre::Vector3(0, 0, 1);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_LEFT))  vt += Ogre::Vector3(-1, 0, 0);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_RIGHT)) vt += Ogre::Vector3(1, 0, 0);

	_camera->moveRelative(vt * evt.timeSinceLastFrame * tSpeed);

	if(_player){
		_player->update(_deltaT);
	}

	return true;
}

bool PlayState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);
	_physicsManager->updatePhysics(_deltaT);

	if (_exitGame)
		return false;
	return true;
}


void PlayState::mouseMoved(const OIS::MouseEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);

	//_camera->yaw(Ogre::Radian(e.state.X.rel) * _deltaT * -1);
	//_camera->pitch(Ogre::Radian(e.state.Y.rel) * _deltaT * -1);
}

void PlayState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/CursorPulsado");
}

void PlayState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Cursor");
}

void PlayState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));

	if (OIS::KC_ESCAPE == e.key){
		_exitGame = true;
	}

	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_C)){		
		_mapGenerator->GenerateMap();
		_player = new Player(_sceneMgr, Ogre::Vector3(_mapGenerator->_mapCenter.x, 5, _mapGenerator->_mapCenter.y), MESHES[Mesh::PLAYERM]);
		_camera->setPosition(_mapGenerator->_mapCenter.x, 15, _mapGenerator->_mapCenter.y - 5);
		_camera->lookAt(_mapGenerator->_mapCenter.x, 0, _mapGenerator->_mapCenter.y);		
	}

	if (OIS::KC_8 == e.key){
		CEGUI::WindowManager::getSingleton().destroyAllWindows();
		changeState(WaveCompleteState::getSingletonPtr());
	}

	if (OIS::KC_9 == e.key){
		CEGUI::WindowManager::getSingleton().destroyAllWindows();
		changeState(GameOverState::getSingletonPtr());
	}
	if (OIS::KC_1 == e.key){

		_hudWeaponsClub->setVisible(true);
		_hudWeaponsGun->setVisible(false);
		_hudWeaponsShotGun->setVisible(false);

	}
	if (OIS::KC_2 == e.key){

		_hudWeaponsClub->setVisible(false);
		_hudWeaponsGun->setVisible(true);
		_hudWeaponsShotGun->setVisible(false);
	}

	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_R)){
		_mapGenerator->cleanMap();
		delete _player;
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


	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(
		"TaharezLook/Cursor");

	// load all the fonts 
	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");

	//Sheet
	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow(
		"DefaultWindow", "Sheet");

	//Config Window	
	playStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"playLayout.layout");



	/*
	_gameOverUI = playStateUI->getChild("FondoGameOver");
	_winUI = playStateUI->getChild("FondoWin");
	_scoreText = _winUI->getChild("LabelScore");
	_scoreTextLose = _gameOverUI->getChild("LabelScore");
	_getReadyText = playStateUI->getChild("GetReady");
	_nameText = _winUI->getChild("NameText");
	_nameTextLose = _gameOverUI->getChild("NameText");
	_scoreTextGUI = playStateUI->getChild("ScoreText");
	_scoreNumberTextGUI = playStateUI->getChild("ScorePlayer");
	_lifeText = playStateUI->getChild("Life");
	_getReadyText->setText("GET READY");
	_saveWin = _winUI->getChild("Save");
	_saveWin->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::save, this));
	_saveGameOver = _gameOverUI->getChild("Exit");
	_saveGameOver->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::save, this));
	_heart1 = playStateUI->getChild("1heart");
	_heart2 = playStateUI->getChild("2heart");
	_heart3 = playStateUI->getChild("3heart");
	_winUI->setVisible(false);
	_gameOverUI->setVisible(false);
	*/
	/*
	_resume->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::resume, this));
	_exitPause->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::quit, this));
	_retry->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::retry, this));
	_exitGameOver->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::quit, this));
	_save->subscribeEvent(CEGUI::PushButton::EventClicked,
	CEGUI::Event::Subscriber(&PlayState::save, this));
	_winUI->setVisible(false);
	_pauseUI->setVisible(false);
	_gameOverUI->setVisible(false);
	*/

	_hud = playStateUI->getChild("HUD");
	_hudLife = _hud->getChild("HUDFULL");
	_hudWeapons = playStateUI->getChild("Weapons");
	_hudWeaponsClub = _hudWeapons->getChild("WeaponClub");
	_hudWeaponsClub->setVisible(true);
	_hudWeaponsGun = _hudWeapons->getChild("WeaponGun");
	_hudWeaponsGun->setVisible(false);
	_hudWeaponsShotGun = _hudWeapons->getChild("WeaponShotGun");
	_hudWeaponsShotGun->setVisible(false);

	sheet->addChild(playStateUI);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
	// INITIALISE OIS MOUSE POSITION TO CEGUI MOUSE POSITION
	OIS::MouseState
		&mutableMouseState =
		const_cast<OIS::MouseState &> (GameManager::getSingletonPtr()->getInputManager()->getMouse()->getMouseState());
	mutableMouseState.X.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x;
	mutableMouseState.Y.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_y;

}