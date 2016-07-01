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
		_camera = _sceneMgr->createCamera("WaveCompleteState");
	}
	createGUI();
	_audioManager = AudioManager::getSingletonPtr();		
}

void WaveCompleteState::exit() {
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}

void WaveCompleteState::pause() {}

void WaveCompleteState::resume() {}

bool WaveCompleteState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

	return true;
}

bool WaveCompleteState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

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
	_audioManager->playAudio(Audio::BACK);

	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(IntroState::getSingletonPtr());
	return true;
}

bool WaveCompleteState::upgrade(const CEGUI::EventArgs &e)
{
	if (_levelGun > 3){
		_upgradeGun->disable();
		_upgradeGun->setAlpha(0.5f);
	}

	if (_levelMines > 3){
		_upgradeClub->disable();
		_upgradeClub->setAlpha(0.5f);
	}

	if (_levelPots > 3){
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

	if (_levelGun == 1){

		scores << " Attack velocity: NORMAL" << "\n" <<
			"Ammo: 16";
		_upgradeGunInfo->setText(scores.str());
	}
	else if (_levelGun == 2){
		scores << " Attack velocity: FAST" << "\n" <<
			"Ammo: 25";
		_upgradeGunInfo->setText(scores.str());
	}
	else if (_levelGun == 3){
		scores << "Imposible more upgrades";
		_upgradeGunInfo->setText(scores.str());
	}

	if (_levelMines == 1){
		scores2 << "Max: 2";
		_upgradeClubInfo->setText(scores2.str());
	}
	else if (_levelMines == 2){
		scores2 << "Max: 3";
		_upgradeClubInfo->setText(scores2.str());
	}
	else if (_levelMines == 3){
		scores2 << "Imposible more upgrades";
		_upgradeClubInfo->setText(scores2.str());
	}

	if (_levelPots == 1){
		scores3 << "Max: 2";
		_upgradeShotGunInfo->setText(scores3.str());
	}
	else if (_levelPots == 2){
		scores3 << "Max: 3";
		_upgradeShotGunInfo->setText(scores3.str());
	}
	else if (_levelPots == 3){
		scores3 << "Imposible more upgrades";
		_upgradeShotGunInfo->setText(scores3.str());
	}

	return true;
}

bool WaveCompleteState::upgradeGun(const CEGUI::EventArgs &e)
{
	if (_levelGun < 3){
		_audioManager->playAudio(Audio::BUTTON);
		_levelGun++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);

	}
	return true;
}
bool WaveCompleteState::upgradeMines(const CEGUI::EventArgs &e)
{
	if (_levelMines < 3){
		_audioManager->playAudio(Audio::BUTTON);
		_levelMines++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);

	}
	return true;
}
bool WaveCompleteState::upgradePots(const CEGUI::EventArgs &e)
{
	if (_levelPots < 3){
		_audioManager->playAudio(Audio::BUTTON);
		_levelPots++;
		_ventanaUpgrade->setVisible(false);
		_ventanaWaveComplete->setVisible(true);
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);
	}

	return true;
}
bool WaveCompleteState::ready(const CEGUI::EventArgs &e)
{
	_audioManager->playAudio(Audio::BUTTON);
	WaveManager::getSingletonPtr()->setLevelGun(_levelGun);
	WaveManager::getSingletonPtr()->setLevelMines(_levelMines);
	WaveManager::getSingletonPtr()->setLevelPots(_levelPots);

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

	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");

	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow(
		"DefaultWindow", "Sheet");

	_waveCompleteStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"WaveComplete.layout");

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

	if (_levelGun == 3 && _levelMines == 3 && _levelPots == 3){
		_upgrade->disable();
		_upgrade->setAlpha(0.5f);
	}

	_ventanaUpgrade->setXPosition(CEGUI::UDim(0.2, 0));
	_ventanaUpgrade->setYPosition(CEGUI::UDim(0.2, 0));

	_ventanaWaveComplete->setXPosition(CEGUI::UDim(0.30, 0));
	_ventanaWaveComplete->setYPosition(CEGUI::UDim(0.20, 0));

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

	OIS::MouseState
		&mutableMouseState =
		const_cast<OIS::MouseState &> (GameManager::getSingletonPtr()->getInputManager()->getMouse()->getMouseState());
	mutableMouseState.X.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x;
	mutableMouseState.Y.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_y;
}