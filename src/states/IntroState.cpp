#include "IntroState.h"
#include "PlayState.h"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter()
{
	_root = Ogre::Root::getSingletonPtr();

	if (_root->hasSceneManager("IntroState") && _sceneMgr->hasCamera(
		"IntroCamera")) {
		_sceneMgr = _root->getSceneManager("IntroState");
		_camera = _sceneMgr->getCamera("IntroCamera");
	}
	else {
		_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "IntroState");
		renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		_camera = _sceneMgr->createCamera("IntroCamera");
	}
	_exitGame = false;

	_physicsManager = new PhysicsManager(_sceneMgr, false);
	_map = new Map(_sceneMgr);
	_map->GenerateMap();

	
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	
	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.18, 0.31, 0.31));
	double width = _viewport->getActualWidth();
	double height = _viewport->getActualHeight();
	_camera->setAspectRatio(width / height);
	_camera->setPosition(Ogre::Vector3(0, 20, 40));
	_camera->lookAt(Ogre::Vector3(0, 0, -100));
	_camera->setNearClipDistance(1);
	_camera->setFarClipDistance(10000);
	_camera->setPosition(_map->getMapCenter().x, 12.5, _map->getMapCenter().y - 5);
	_camera->lookAt(_map->getMapCenter().x, 0, _map->getMapCenter().y);
	
	
	createGUI();

	if (!_audioManager){
		_audioManager = new AudioManager();

	}
	_audioManager->playAudio(Audio::INTROSTATE);
}

void IntroState::exit()
{
	delete _physicsManager;
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}

void IntroState::pause(){}

void IntroState::resume(){}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt)
{
	_timeSinceLastFrame = evt.timeSinceLastFrame;
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		_timeSinceLastFrame);

	return true;
}

bool IntroState::frameEnded(const Ogre::FrameEvent& evt){
	if (_exitGame)
		return false;
	return true;
}

void IntroState::keyPressed(const OIS::KeyEvent &e) {

	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);

	if (!_credits && !_highscore && e.key == OIS::KC_Z) {
		_audioManager->playAudio(Audio::BACK);

		_exitGame = true;
	}
	if (_credits && e.key == OIS::KC_ESCAPE) {
		_audioManager->playAudio(Audio::BACK);

		exitButton->setVisible(true);
		playButton->setVisible(true);
		highscoreButton->setVisible(true);
		creditsButton->setVisible(true);
		fondoCredits->setVisible(false);
		fondoScore->setVisible(false);
		_credits = false;

	}
	if (e.key == OIS::KC_ESCAPE && _highscore) {
		_audioManager->playAudio(Audio::BACK);

		introStateUI->setVisible(true);
		exitButton->setVisible(true);
		playButton->setVisible(true);
		highscoreButton->setVisible(true);
		creditsButton->setVisible(true);
		fondoCredits->setVisible(false);
		fondoScore->setVisible(false);
		_highscore = false;
	}
}

void IntroState::keyReleased(const OIS::KeyEvent &e) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		static_cast<CEGUI::Key::Scan> (e.key));
}

void IntroState::mouseMoved(const OIS::MouseEvent &e) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);
}

void IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/CursorPulsado");
}

void IntroState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Cursor");
}

IntroState* IntroState::getSingletonPtr(){
	return msSingleton;
}

IntroState& IntroState::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}

bool IntroState::play(const CEGUI::EventArgs &e) {

	_audioManager->playAudio(Audio::PLAY);

	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(PlayState::getSingletonPtr());

	return true;
}

bool IntroState::quit(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BACK);

	_exitGame = true;
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
	return true;
}

bool IntroState::highscore(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BUTTON);

	std::fstream ficheroEntrada;
	StringStream texto;
	String frase;

	ficheroEntrada.open("stat.txt");
	if (ficheroEntrada.is_open()) {

		while (!ficheroEntrada.eof()) {
			getline(ficheroEntrada, frase);
			texto << frase << "\n";
		}
		_highScoreText->setText(texto.str());

		ficheroEntrada.close();
	}

	_highscore = true;
	_highScoreText->setVisible(true);
	instruccionesButton->setVisible(false);
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(true);
	fondoInstrucciones->setVisible(false);

	return true;
}
bool IntroState::credits(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BUTTON);

	_credits = true;
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	instruccionesButton->setVisible(false);

	fondoCredits->setVisible(true);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(false);

	return true;
}

bool IntroState::instrucciones(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BUTTON);

	instruccionesButton->setVisible(false);
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	instruccionesButton->setVisible(false);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(true);

	return true;
}
bool IntroState::atras(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BACK);

	exitButton->setVisible(true);
	playButton->setVisible(true);
	highscoreButton->setVisible(true);
	creditsButton->setVisible(true);
	instruccionesButton->setVisible(true);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(false);

	return true;
}

bool IntroState::control(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BUTTON);

	_controlText->setVisible(true);
	_tutorialText->setVisible(false);
	return true;
}

bool IntroState::tutorial(const CEGUI::EventArgs &e) {
	_audioManager->playAudio(Audio::BUTTON);

	_controlText->setVisible(false);
	_tutorialText->setVisible(true);

	return true;
}

void IntroState::createGUI() {

	//CEGUI	
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(
		"DejaVuSans-12");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(
		"TaharezLook/Cursor");

	//Sheet
	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow(
		"DefaultWindow", "Ex1/Sheet");

	introStateUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
		"introState.layout");

	exitButton = introStateUI->getChild("Salir");
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::quit, this));
	playButton = introStateUI->getChild("Play");
	playButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::play, this));
	highscoreButton = introStateUI->getChild("Score");
	highscoreButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::highscore, this));
	creditsButton = introStateUI->getChild("Credits");
	creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::credits, this));
	instruccionesButton = introStateUI->getChild("Instrucciones");
	instruccionesButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::instrucciones, this));


	fondoCredits = introStateUI->getChild("VentanaCredits");
	fondoScore = introStateUI->getChild("VentanaScore");
	fondoInstrucciones = introStateUI->getChild("VentanaInstrucciones");
	fondoInstrucciones->setVisible(false);
	_controlText = fondoInstrucciones->getChild("LabelInstrucciones");
	_controlText->setVisible(true);
	_tutorialText = fondoInstrucciones->getChild("LabelTutorial");
	_tutorialText->setVisible(false);
	_control = fondoInstrucciones->getChild("Control");
	_control->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::control, this));
	_tutorial = fondoInstrucciones->getChild("Tutorial");
	_tutorial->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::tutorial, this));

	_atrasInstrucciones = fondoInstrucciones->getChild("AtrasInstrucciones");
	_atrasInstrucciones->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));
	_atrasScores = fondoScore->getChild("AtrasScore");
	_highScoreText = fondoScore->getChild("SCORE");
	_atrasScores->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));
	_atrasCredits = fondoCredits->getChild("AtrasCredits");
	_atrasCredits->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));

	sheet->addChild(introStateUI);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

//Conversion mouse
CEGUI::MouseButton IntroState::convertMouseButton(OIS::MouseButtonID id) {
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