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
		_camera = _sceneMgr->createCamera("GameOverState");
	}

	createGUI();	

	_audioManager = AudioManager::getSingletonPtr();
	_audioManager->playAudio(Audio::INTROSTATE);
}

void GameOverState::exit() {
	WaveManager::getSingletonPtr()->resetWaveManager();
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}

void GameOverState::pause() {}

void GameOverState::resume() {}

bool GameOverState::frameStarted(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);

	return true;
}

bool GameOverState::frameEnded(const Ogre::FrameEvent& evt){
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		evt.timeSinceLastFrame);
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

void GameOverState::checkScore(){

	std::ifstream ficheroEntrada;
	String frase;

	ficheroEntrada.open("scores.txt");
	getline(ficheroEntrada, frase);
	int a = WaveManager::getSingletonPtr()->getLevel();
	int b = atoi(frase.c_str());
	if (b < a){
		frase = std::to_string(a);
	}

	ficheroEntrada.close();

	std::ofstream ficheroSalida;
	ficheroSalida.open("scores.txt");
	ficheroSalida << frase;
	ficheroSalida.close();
}

void GameOverState::statScore(){


	std::ifstream ficheroEntrada;
	String frase;
	StringStream statsText;
	std::cout << WaveManager::getSingletonPtr()->getPotsUsed() << std::endl; 
	std::ofstream ficheroSalida;
	ficheroSalida.open("stat.txt");
	statsText << "TIME. . . . . . . . . . . . . . . . . . . . . . . . " << WaveManager::getSingletonPtr()->getGameTime()*60 << " \n" << " \n"
		<< "LEVEL. . . . . . . . . . . . . . . . . . . . . . . . . . " << WaveManager::getSingletonPtr()->getLevel() << " \n" << " \n"
		<< "ENEMIES. . . . . . . . . . . . . . . . . . . . . . . . . " << WaveManager::getSingletonPtr()->getEnemiesKilled() << " \n" << " \n"
		<< "MINES. . . . . . . . . . . . . . . . . . . . . . . . . . " << WaveManager::getSingletonPtr()->getMinesUsed() << " \n" << " \n"
		<< "BULLETS. . . . . . . . . . . . . . . . . . . . . . . . . " << WaveManager::getSingletonPtr()->getBulletsUsed() << " \n" << " \n"
		<< "POTS. . . . . . . . . . . . . . . . . . . . . . . . . . ." << WaveManager::getSingletonPtr()->getPotsUsed() << " \n" << " \n";		

	frase = statsText.str();
	ficheroSalida << frase;
	ficheroSalida.close();
}
bool GameOverState::quit(const CEGUI::EventArgs &e)
{	
	checkScore();
	statScore();

	_audioManager->playAudio(Audio::BACK);
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	WaveManager::getSingletonPtr()->resetWaveManager();
	changeState(IntroState::getSingletonPtr());
	return true;
}


bool GameOverState::ready(const CEGUI::EventArgs &e)
{
	_audioManager->playAudio(Audio::BUTTON);

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
	
	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");
	
	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow(
		"DefaultWindow", "Sheet");
	
	_GameOverStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"gameOver.layout");

	_ventanaGameOver = _GameOverStateUI->getChild("VentanaGameOver");
	_exit = _ventanaGameOver->getChild("Exit");
	_exit->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverState::quit, this));

	_timeGame = _ventanaGameOver->getChild("Tiempo");
	std::stringstream timeGame;
	timeGame << WaveManager::getSingletonPtr()->getGameTime()/60;
	_timeGame->setText(timeGame.str());

	_level = _ventanaGameOver->getChild("Nivel");
	std::stringstream level;
	level << WaveManager::getSingletonPtr()->getLevel();
	_level->setText(level.str());

	_enemies = _ventanaGameOver->getChild("Enemigos");
	std::stringstream enemies;
	enemies << WaveManager::getSingletonPtr()->getEnemiesKilled();
	_enemies->setText(enemies.str());

	_boss = _ventanaGameOver->getChild("Boss");
	std::stringstream boss;
	boss << WaveManager::getSingletonPtr()->getMinesUsed();
	_boss->setText(boss.str());

	_bullets = _ventanaGameOver->getChild("Balas");
	std::stringstream bullets;
	bullets << WaveManager::getSingletonPtr()->getBulletsUsed();
	_bullets->setText(bullets.str());

	_pots = _ventanaGameOver->getChild("Pociones");
	std::stringstream pots;
	pots << WaveManager::getSingletonPtr()->getBulletsUsed();
	_pots->setText(pots.str());


	_ventanaGameOver->setXPosition(CEGUI::UDim(0.30,0));
	_ventanaGameOver->setYPosition(CEGUI::UDim(0.20, 0));
	
	sheet->addChild(_GameOverStateUI);


	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
	
	OIS::MouseState
		&mutableMouseState =
		const_cast<OIS::MouseState &> (GameManager::getSingletonPtr()->getInputManager()->getMouse()->getMouseState());
	mutableMouseState.X.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x;
	mutableMouseState.Y.abs
		= CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_y;

}