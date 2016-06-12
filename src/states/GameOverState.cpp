#include "GameOverState.h"
#include "PlayState.h";
#include "IntroState.h";
template<> GameOverState* Ogre::Singleton<GameOverState>::msSingleton = 0;

void GameOverState::enter()
{
	_root = Ogre::Root::getSingletonPtr();

	if (_root->hasSceneManager("GameOverState") && _sceneMgr->hasCamera(
		"GameOverState")) {
		_sceneMgr = _root->getSceneManager("GameOverState");
		_camera = _sceneMgr->getCamera("GameOverState");
	}
	else {
		_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "GameOverState");
		//Inicializacion de CEGUI
		//_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		// set camera
		_camera = _sceneMgr->createCamera("GameOverState");
	}

	createGUI();
	_exitGame = false;
	
	

	//_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);

}

void GameOverState::exit() {
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();

}

void GameOverState::pause() {

}

void GameOverState::resume() {

}

bool GameOverState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);



	return true;
}

bool GameOverState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);


	if (_exitGame)
		return false;
	return true;
}


void GameOverState::mouseMoved(const OIS::MouseEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);
}

void GameOverState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/CursorPulsado");
}

void GameOverState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Cursor");
}

void GameOverState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));

	if (OIS::KC_ESCAPE == e.key){
		_exitGame = true;
	}
	//Test scale real time animation
	/*
	if (OIS::KC_M == e.key){
		CEGUI::WindowManager::getSingleton().destroyAllWindows();
		sizeX = sizeX + 0.1;
		createGUI();
	}
	*/
}

void GameOverState::keyReleased(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		static_cast<CEGUI::Key::Scan> (e.key));

}

GameOverState* GameOverState::getSingletonPtr()
{
	return msSingleton;
}

GameOverState& GameOverState::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}
CEGUI::MouseButton GameOverState::convertMouseButton(OIS::MouseButtonID id)
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


bool GameOverState::quit(const CEGUI::EventArgs &e)
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(IntroState::getSingletonPtr());
	return true;
}




bool GameOverState::ready(const CEGUI::EventArgs &e)
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(PlayState::getSingletonPtr());
	return true;
}
void GameOverState::createGUI()
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
	_GameOverStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"gameOver.layout");



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
	/*
	_ventanaUpgrade = _GameOverStateUI->getChild("VentanaUpgrade");
	_ventanaUpgrade->setVisible(false);
	_ventanaWaveComplete = _GameOverStateUI->getChild("VentanaWaveComplete");

	_upgradeClub = _ventanaUpgrade->getChild("UpgradeClub");
	_upgradeGun = _ventanaUpgrade->getChild("UpgradeGun");
	_upgradeShotGun = _ventanaUpgrade->getChild("UpgradeShotGun");

	_ready = _ventanaWaveComplete->getChild("Upgrade");
	_upgrade = _ventanaWaveComplete->getChild("Ready");
	_exit = _ventanaWaveComplete->getChild("Salir");

	_exit->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::quit, this));
	_upgrade->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::upgrade, this));

	_upgradeClub->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::upgradeWeapon, this));

	_upgradeGun->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::upgradeWeapon, this));

	_upgradeShotGun->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::upgradeWeapon, this));

	_ready->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::ready, this));
		*/

	_ventanaGameOver = _GameOverStateUI->getChild("VentanaGameOver");
	_exit = _ventanaGameOver->getChild("Exit");
	_exit->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::quit, this));

	_timeGame = _ventanaGameOver->getChild("Tiempo");
	std::stringstream timeGame;
	timeGame << WaveManager::getSingletonPtr()->timeGame();
	_timeGame->setText(timeGame.str());

	_level = _ventanaGameOver->getChild("Nivel");
	std::stringstream level;
	level << WaveManager::getSingletonPtr()->levelPlayer();
	_level->setText(level.str());

	_enemies = _ventanaGameOver->getChild("Enemigos");
	std::stringstream enemies;
	enemies << WaveManager::getSingletonPtr()->countEnemies();
	_enemies->setText(enemies.str());

	_boss = _ventanaGameOver->getChild("Boss");
	std::stringstream boss;
	boss << WaveManager::getSingletonPtr()->countBoss();
	_boss->setText(boss.str());

	_bullets = _ventanaGameOver->getChild("Balas");
	std::stringstream bullets;
	bullets << WaveManager::getSingletonPtr()->countBullets();
	_bullets->setText(bullets.str());

	_pots = _ventanaGameOver->getChild("Pociones");
	std::stringstream pots;
	pots << WaveManager::getSingletonPtr()->countPots();
	_pots->setText(pots.str());


	//_ventanaGameOver->setXPosition(CEGUI::UDim(0.50,0));
	
	//Test scale real time animation
	//_ventanaGameOver->setSize(CEGUI::USize(CEGUI::UDim(sizeX, 0), CEGUI::UDim(0.05, 0)));
	
	sheet->addChild(_GameOverStateUI);


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