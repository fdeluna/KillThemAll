#include "waveCompleteState.h"
#include "PlayState.h";
#include "IntroState.h";
template<> WaveCompleteState* Ogre::Singleton<WaveCompleteState>::msSingleton = 0;

void WaveCompleteState::enter()
{
	_root = Ogre::Root::getSingletonPtr();

	if (_root->hasSceneManager("WaveCompleteState") && _sceneMgr->hasCamera(
		"WaveCompleteState")) {
		_sceneMgr = _root->getSceneManager("WaveCompleteState");
		_camera = _sceneMgr->getCamera("WaveCompleteState");
	}
	else {
		_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "WaveCompleteState");
		//Inicializacion de CEGUI
		//_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		// set camera
		_camera = _sceneMgr->createCamera("WaveCompleteState");
	}
	//_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	createGUI();
	_exitGame = false;
	//_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	audioController = AudioController::getSingletonPtr();



}

void WaveCompleteState::exit() {
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();

}

void WaveCompleteState::pause() {

}

void WaveCompleteState::resume() {

}

bool WaveCompleteState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);



	return true;
}

bool WaveCompleteState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);


	if (_exitGame)
		return false;
	return true;
}


void WaveCompleteState::mouseMoved(const OIS::MouseEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);
}

void WaveCompleteState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/CursorPulsado");
}

void WaveCompleteState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Cursor");
}

void WaveCompleteState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));

	if (OIS::KC_ESCAPE == e.key){
		_exitGame = true;
	}


}

void WaveCompleteState::keyReleased(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		static_cast<CEGUI::Key::Scan> (e.key));

}

WaveCompleteState* WaveCompleteState::getSingletonPtr()
{
	return msSingleton;
}

WaveCompleteState& WaveCompleteState::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}
CEGUI::MouseButton WaveCompleteState::convertMouseButton(OIS::MouseButtonID id)
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


bool WaveCompleteState::quit(const CEGUI::EventArgs &e)
{
	audioController->playAudio(Audio::BACK);

	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(IntroState::getSingletonPtr());
	return true;
}

bool WaveCompleteState::upgrade(const CEGUI::EventArgs &e)
{

	if (levelGun > 3){
		_upgradeGun->disable();
		_upgradeGun->setAlpha(0.5f);
	}

	if (levelMines > 3){
		_upgradeClub->disable();
		_upgradeClub->setAlpha(0.5f);
	}

	if (levelPots > 3){
		_upgradeShotGun->disable();
		_upgradeShotGun->setAlpha(0.5f);
	}

	_ventanaWaveComplete->setVisible(false);
	_ventanaUpgrade->setVisible(true);
	std::stringstream scores;
	std::stringstream scores2;
	std::stringstream scores3;

	scores.clear();
	scores2.clear();
	scores3.clear();

	


	if (levelGun == 1){

		scores << "Damage: 3" << "\n" << " Attack velocity: NORMAL" << "\n" <<
			"Ammo: 16";
		_upgradeGunInfo->setText(scores.str());
	}
	else if (levelGun == 2){
		scores << "Damage: 4" << "\n" << " Attack velocity: FAST" << "\n" <<
			"Ammo: 25";
		_upgradeGunInfo->setText(scores.str());
	}
	else if (levelGun == 3){
		scores << "Imposible more upgrades";
		_upgradeGunInfo->setText(scores.str());
	}

	if (levelMines == 1){

		scores2 << "Max: 2";
		_upgradeClubInfo->setText(scores2.str());
	}
	else if (levelMines == 2){
		scores2 << "Max: 3";
		_upgradeClubInfo->setText(scores2.str());
	}
	else if (levelMines == 3){
		scores2 << "Imposible more upgrades";
		_upgradeClubInfo->setText(scores2.str());
	}
	

	if (levelPots == 1){

		scores3 << "Max: 2";
		_upgradeShotGunInfo->setText(scores3.str());
	}
	else if (levelPots == 2){
		scores3<< "Max: 3";
		_upgradeShotGunInfo->setText(scores3.str());
	}
	else if (levelPots == 3){
		scores3 << "Imposible more upgrades";
		_upgradeShotGunInfo->setText(scores3.str());
	}
	
	
	
	
	

	return true;
}

bool WaveCompleteState::upgradeGun(const CEGUI::EventArgs &e)
{
	
	if (levelGun < 3){
		audioController->playAudio(Audio::BUTTON);
		levelGun++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);
		
	}
	

	

	return true;
}
bool WaveCompleteState::upgradeMines(const CEGUI::EventArgs &e)
{

	if (levelMines < 3){
		audioController->playAudio(Audio::BUTTON);
		levelMines++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);

	}




	return true;
}
bool WaveCompleteState::upgradePots(const CEGUI::EventArgs &e)
{

	if (levelPots < 3){
		audioController->playAudio(Audio::BUTTON);
		levelPots++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);

	}




	return true;
}
bool WaveCompleteState::ready(const CEGUI::EventArgs &e)
{
	audioController->playAudio(Audio::BUTTON);
	WaveManager::getSingletonPtr()->setLevelGun(levelGun);
	WaveManager::getSingletonPtr()->setLevelMines(levelMines);
	WaveManager::getSingletonPtr()->setLevelPots(levelPots);

	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(PlayState::getSingletonPtr());
	return true;
}
void WaveCompleteState::createGUI()
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
	_waveCompleteStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"WaveComplete.layout");



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
	_ventanaUpgrade = _waveCompleteStateUI->getChild("VentanaUpgrade");
	_ventanaUpgrade->setVisible(false);
	_ventanaWaveComplete = _waveCompleteStateUI->getChild("VentanaWaveComplete");

	_upgradeClub = _ventanaUpgrade->getChild("UpgradeClub");
	_upgradeGun = _ventanaUpgrade->getChild("UpgradeGun");
	_upgradeShotGun = _ventanaUpgrade->getChild("UpgradeShotGun");
	_upgradeClubInfo = _ventanaUpgrade->getChild("ClubInfo");
	_upgradeGunInfo = _ventanaUpgrade->getChild("GunInfo");
	_upgradeShotGunInfo = _ventanaUpgrade->getChild("ShotGunInfo");

	_ready = _ventanaWaveComplete->getChild("Upgrade");
	_upgrade = _ventanaWaveComplete->getChild("Ready");
	_exit = _ventanaWaveComplete->getChild("Salir");

	_exit->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::quit, this));
	_upgrade->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::upgrade, this));
	
	_upgradeClub->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::upgradeMines, this));

	_upgradeGun->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::upgradeGun, this));

	_upgradeShotGun->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::upgradePots, this));

	_ready->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&WaveCompleteState::ready, this));
	sheet->addChild(_waveCompleteStateUI);

	if (levelGun == 3 && levelMines == 3 && levelPots ==3){
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);
	}


	//Recolocate windows
	_ventanaUpgrade->setXPosition(CEGUI::UDim(0.2, 0));
	_ventanaUpgrade->setYPosition(CEGUI::UDim(0.2, 0));

	_ventanaWaveComplete->setXPosition(CEGUI::UDim(0.30, 0));
	_ventanaWaveComplete->setYPosition(CEGUI::UDim(0.20, 0));

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