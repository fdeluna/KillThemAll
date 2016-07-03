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
		_camera = _sceneMgr->createCamera("PlayState");
		_waveManager = new WaveManager(_sceneMgr);
	}
	init();
	createGUI();
	_state = GameFlowState::PLAY;
}

void  PlayState::init(){
	
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	Ogre::Light* light;
	light = _sceneMgr->createLight("LightingNode");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, -3));
	_sceneMgr->getRootSceneNode()->attachObject(light);

	_physicsManager = new PhysicsManager(_sceneMgr, false);
	
	_delay = 0;
	_startDelay = 0;	
	_waveManager->cleanWave();
	_waveManager->initWave();
	_player = new Player(_sceneMgr, Ogre::Vector3(_waveManager->getMap()->getMapCenter().x, 1, _waveManager->getMap()->getMapCenter().y), MESHES[MeshName::PLAYERM]);
	_player->setLevel(_waveManager->levelPlayer());
	_waveManager->setPlayer(_player);
	_pathFinder = new PathFinder(_waveManager->getMap());

	
	Ogre::Vector3 weaponPosition = Ogre::Vector3(_player->getSceneNodeComponent()->getSceneNode()->getPosition().x + 15,
		_player->getSceneNodeComponent()->getSceneNode()->getPosition().y,
		_player->getSceneNodeComponent()->getSceneNode()->getPosition().z);
	_gun = new Gun(_player, _player->getSceneNodeComponent()->getSceneManager(), weaponPosition, MESHES[MeshName::REVOLVER]);

	
	updateLevelWeapons();

	
	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.18, 0.31, 0.31));
	double width = _viewport->getActualWidth();
	double height = _viewport->getActualHeight();
	_camera->setAspectRatio(width / height);
	_camera->setPosition(Ogre::Vector3(0, 20, 40));
	_camera->lookAt(Ogre::Vector3(0, 0, -100));
	_camera->setNearClipDistance(1);
	_camera->setFarClipDistance(10000);
	_camera->setPosition(_waveManager->getMap()->getMapCenter().x, 12.5, _waveManager->getMap()->getMapCenter().y - 5);
	_camera->lookAt(_waveManager->getMap()->getMapCenter().x, 0, _waveManager->getMap()->getMapCenter().y);

	_audioManager = AudioManager::getSingletonPtr();
	_audioManager->playAudio(Audio::PLAYSTATE);

	//PARTICLE
	nodeParticlePotion = _sceneMgr->createSceneNode("NodeParticulaMine");
	nodeParticlePotion->setScale(0.3, 0.3, 0.3);
	_player->getSceneNodeComponent()->getSceneNode()->addChild(nodeParticlePotion);
	nodeParticlePotion->setPosition(_player->getSceneNodeComponent()->getSceneNode()->getPosition());
	partSystemPotion = _sceneMgr->createParticleSystem("Potion", "Potion");
	nodeParticlePotion->attachObject(partSystemPotion);
	partSystemPotion->setVisible(false);

	nodeParticleFire = _sceneMgr->createSceneNode("NodeParticulaFire");
	nodeParticleFire->setScale(0.01, 0.01, 0.01);

	_sceneMgr->getRootSceneNode()->addChild(nodeParticleFire);
	nodeParticleFire->setPosition(Ogre::Vector3(-5, -10, 0));
	partSystemFire = _sceneMgr->createParticleSystem("Fire", "FireFloor");
	nodeParticleFire->attachObject(partSystemFire);
	partSystemFire->setVisible(true);


	nodeParticleFire2 = _sceneMgr->createSceneNode("NodeParticulaFire2");
	nodeParticleFire2->setScale(0.03, 0.01, 0.03);

	_sceneMgr->getRootSceneNode()->addChild(nodeParticleFire2);
	nodeParticleFire2->setPosition(Ogre::Vector3(5, -10, 0));
	partSystemFire2 = _sceneMgr->createParticleSystem("Fire2", "FireFloor");
	nodeParticleFire2->attachObject(partSystemFire2);
	partSystemFire2->setVisible(true);
}

void PlayState::exit() {
	_waveManager->cleanWave();
	_mine = nullptr;
	delete _pathFinder;
	_player = nullptr;
	_sceneMgr->clearScene();
	delete _physicsManager;
}


void PlayState::pause() {}


void PlayState::resume() {}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

	_deltaT = evt.timeSinceLastFrame;
	_startDelay += _deltaT;
	_physicsManager->updatePhysics(_deltaT);
	printTextGUI();
	timeParticlePotion += _deltaT;

	//Particle
	if (timeParticlePotion > 0.5){
		partSystemPotion->setVisible(false);
	}

	partSystemFire->_update(2 * _deltaT);
	partSystemFire2->_update(2 * _deltaT);

	if (nodeParticlePotion){
		nodeParticlePotion->setPosition(_player->getSceneNodeComponent()->getSceneNode()->getPosition());
		partSystemPotion->_update(4 * _deltaT);
	}

	switch (_state){
	case GameFlowState::PLAY:

		if (_mine && _mine->isActive()){
			_mine->update(_deltaT);
		}
		else{
			_mine = nullptr;
		}

		if (_gun){

			_gun->update(evt);

			if (timer > _gun->getVelAtack()){
				_gun->setCanShoot(true);
				timer = 0;
			}
			if (_gun->getReloading()){
				timerReload = timerReload + evt.timeSinceLastFrame;
			}
			if (timerReload > 1 && _gun->getReloading()){
				_gun->reload();
				_gun->setReloading(false);

			}
		}

		if (_player){
			hudLife();
			if (_player->getLife() <= 0){
				_delay = 0;
				_state = GameFlowState::GAMEOVER;
			}
			_player->update(_deltaT);
			_waveManager->wave(_deltaT);
		}

		if (_waveManager->getWaveEnemiesKilled() >= _waveManager->getWaveEnemies()){
			_delay = 0;
			_state = GameFlowState::WAVECLEARED;
		}

		break;
	case GameFlowState::GAMEOVER:
		_delay += _deltaT;
		if (_delay > 3){
			_waveManager->setGameTime(_deltaT);
			_waveManager->setBulletUsed(_gun->getNumBullet());
			_waveManager->setMinesUsed(numMines);
			_waveManager->setPotsUsed(numPots);			
			changeState(GameOverState::getSingletonPtr());
		}
		break;
	case GameFlowState::WAVECLEARED:
		_delay += _deltaT;
		StringStream waveComplete;
		waveComplete << "WAVE CLEARED!!!";
		_centralText->setText(waveComplete.str());
		if (_delay > 3){
			_player->levelUp();
			changeState(WaveCompleteState::getSingletonPtr());
		}
		break;
	}
	return true;
}

bool PlayState::frameEnded(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);
	_physicsManager->updatePhysics(_deltaT);

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
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Mirilla");

	if (_state == GameFlowState::PLAY){
		//Use pots
		if (_hudWeaponsShotGun->isVisible()){
			if (_player->getPotions() > 0){

				_audioManager->playAudio(Audio::POTION);

				_player->potion();
				partSystemPotion->setVisible(true);
				timeParticlePotion = 0;
				numPots++;
			}
			hudLife();
		}
		else if (_hudWeaponsClub->isVisible()){
			_gun->shoot();


		}
		else if (_hudWeaponsGun->isVisible()){

			if (_mine){
				_mine->active();
			}
			else{
				Ogre::Vector3 positionMine = Ogre::Vector3(_player->getSceneNodeComponent()->getSceneNode()->getPosition());

				if (_player->getCountMines() > 0){
					_audioManager->playAudio(Audio::MINE);

					_mine = new Mine(_sceneMgr, Ogre::Vector3(positionMine.x, 0.5, positionMine.z), MESHES[MeshName::MINE], GameObjectType::MINES);
					_player->setCountMines(_player->getCountMines() - 1);
					numMines++;
				}
			}
		}
	}
}

void PlayState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Mirilla");
}

void PlayState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));

	if (OIS::KC_1 == e.key){
		_audioManager->playAudio(Audio::BUTTON);

		_hudWeaponsClub->setVisible(true);
		_hudWeaponsGun->setVisible(false);
		_hudWeaponsShotGun->setVisible(false);

	}
	if (OIS::KC_2 == e.key){
		_audioManager->playAudio(Audio::BUTTON);

		_hudWeaponsClub->setVisible(false);
		_hudWeaponsGun->setVisible(true);
		_hudWeaponsShotGun->setVisible(false);
	}
	if (OIS::KC_3 == e.key){
		_audioManager->playAudio(Audio::BUTTON);

		_hudWeaponsClub->setVisible(false);
		_hudWeaponsGun->setVisible(false);
		_hudWeaponsShotGun->setVisible(true);
	}

	if (OIS::KC_R == e.key){
		_gun->setReloading(true);
		_gun->reload();
		timerReload = 0;
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

void PlayState::hudLife()
{
	if (_player->getLife() < 2){

		_vida1->setVisible(true);
		_vida2->setVisible(false);
		_vida3->setVisible(false);
		_vida4->setVisible(false);
		_vida5->setVisible(false);
		_vida6->setVisible(false);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 3){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(false);
		_vida4->setVisible(false);
		_vida5->setVisible(false);
		_vida6->setVisible(false);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 4){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(false);
		_vida5->setVisible(false);
		_vida6->setVisible(false);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 5){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(true);
		_vida5->setVisible(false);
		_vida6->setVisible(false);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 6){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(true);
		_vida5->setVisible(true);
		_vida6->setVisible(false);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 7){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(true);
		_vida5->setVisible(true);
		_vida6->setVisible(true);
		_vida7->setVisible(false);
		_vida8->setVisible(false);
	}
	else if (_player->getLife() < 8){
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(true);
		_vida5->setVisible(true);
		_vida6->setVisible(true);
		_vida7->setVisible(true);
		_vida8->setVisible(false);


	}
	else{
		_vida1->setVisible(true);
		_vida2->setVisible(true);
		_vida3->setVisible(true);
		_vida4->setVisible(true);
		_vida5->setVisible(true);
		_vida6->setVisible(true);
		_vida7->setVisible(true);
		_vida8->setVisible(true);
	}




}
void PlayState::printTextGUI(){
	
	StringStream enemiesString2;
	enemiesString2 << "WAVE: " << _waveManager->levelPlayer();
	_wave->setText(enemiesString2.str());

	StringStream enemiesString;
	enemiesString << "ENEMIES: " << _waveManager->getWaveEnemies() - _waveManager->getWaveEnemiesKilled();
	_enemies->setText(enemiesString.str());

	StringStream enemiesString3;
	enemiesString3 << _player->getCountMines();
	_minesGUI->setText(enemiesString3.str());

	StringStream enemiesString4;
	enemiesString4 << _player->getPotions();
	_potGUI->setText(enemiesString4.str());

	StringStream enemiesString5;
	enemiesString5 << _gun->getAmmo();
	_bulletsGUI->setText(enemiesString5.str());

	if (_startDelay < 3){
		StringStream enemiesString6;
		enemiesString6 << "LEVEL: " << _player->getLevel();
		_centralText->setText(enemiesString6.str());
	}
	else{
		StringStream enemiesString6;
		enemiesString6 << "";
		_centralText->setText(enemiesString6.str());
	}

	if (_gun->getAmmo() < 1){
		StringStream enemiesString6;
		enemiesString6 << "RELOAD!";
		_centralText->setText(enemiesString6.str());
	}
	else if (_gun->getReloading()){
		StringStream enemiesString6;
		enemiesString6 << "RELOADING . . .";
		_centralText->setText(enemiesString6.str());
	}


	if (_player->getLife() < 1){
		StringStream enemiesString6;
		enemiesString6 << _player->getTextDie();
		_centralText->setText(enemiesString6.str());

	}

	if (_player->getLife() <= _player->getMaxLife() / 2){
		timerWarning += _deltaT;
		if (0 < timerWarning && timerWarning < 0.5){
			_warning->setVisible(true);
		}
		else if (0.5 < timerWarning && timerWarning < 1){
			_warning->setVisible(false);

		}
		else if (1 < timerWarning && timerWarning < 1.5){
			timerWarning = 0;
		}
	}
	else{

		_warning->setVisible(false);

	}

}

void PlayState::updateLevelWeapons(){
	_gun->setLevelGun(WaveManager::getSingletonPtr()->getLevelGun());
	_player->setLevelMines(WaveManager::getSingletonPtr()->getLevelMines());
	_player->setLevelPots(WaveManager::getSingletonPtr()->getLevelPots());
	_gun->upgrade();
	_player->levelUpMines();
	_player->levelUpPotion();
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
		"TaharezLook/Mirilla");
	
	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");
	
	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow(
		"DefaultWindow", "Sheet");
	
	playStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"PlayState.layout");

	_hud = playStateUI->getChild("HUD");
	_hudLife = _hud->getChild("HUDFULL");
	_vida1 = _hud->getChild("Vida1");
	_vida2 = _hud->getChild("Vida2");
	_vida3 = _hud->getChild("Vida3");
	_vida4 = _hud->getChild("Vida4");
	_vida5 = _hud->getChild("Vida5");
	_vida6 = _hud->getChild("Vida6");
	_vida7 = _hud->getChild("Vida7");
	_vida8 = _hud->getChild("Vida8");
	_enemies = playStateUI->getChild("ENEMIES");
	_wave = playStateUI->getChild("WAVE");

	_minesGUI = playStateUI->getChild("TEXTSLOT1");
	_bulletsGUI = playStateUI->getChild("TEXTSLOT2");
	_potGUI = playStateUI->getChild("TEXTSLOT3");
	_centralText = playStateUI->getChild("CENTRALTEXT");
	_levelText = playStateUI->getChild("CENTRALTEXT2");
	_warning = playStateUI->getChild("CENTRALTEXT3");
	_warning->setVisible(false);
	_levelText->setVisible(true);
	_enemies->setVisible(true);
	_hudLife->setVisible(true);
	_vida1->setVisible(true);
	_vida2->setVisible(true);
	_vida3->setVisible(true);
	_vida4->setVisible(true);
	_vida5->setVisible(true);
	_vida6->setVisible(true);
	_vida7->setVisible(true);
	_vida8->setVisible(true);

	_hudWeapons = playStateUI->getChild("Weapons");
	_hudWeaponsClub = _hudWeapons->getChild("WeaponClub");
	_hudWeaponsClub->setVisible(true);
	_hudWeaponsGun = _hudWeapons->getChild("WeaponGun");
	_hudWeaponsGun->setVisible(false);
	_hudWeaponsShotGun = _hudWeapons->getChild("WeaponShotGun");
	_hudWeaponsShotGun->setVisible(false);

	StringStream levelString;
	levelString << _player->getLevel();
	_levelText->setText(levelString.str());
	sheet->addChild(playStateUI);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
	
	OIS::MouseState
		&mutableMouseState =
		const_cast<OIS::MouseState &> (GameManager::getSingletonPtr()->getInputManager()->getMouse()->getMouseState());
	mutableMouseState.X.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x;
	mutableMouseState.Y.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_y;

}