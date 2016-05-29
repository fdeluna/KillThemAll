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
		//Inicializacion de CEGUI
		renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		// set camera
		_camera = _sceneMgr->createCamera("IntroCamera");
	}
	

	_exitGame = false;

	//Camera
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	_camera->setNearClipDistance(5);
	_camera->setFarClipDistance(10000);
	_camera->setPosition(0, 15, 10);
	_camera->lookAt(0, 0, 0);

	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
	//CEGUI
	createGUI();

	_mapGenerator = new MapGenerator(_sceneMgr);
	_mapGenerator->GenerateMap();
}

void
IntroState::exit()
{
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause()
{
}

void
IntroState::resume()
{
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt)
{
	_timeSinceLastFrame = evt.timeSinceLastFrame;
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
		_timeSinceLastFrame);

	_mapGenerator->update(evt.timeSinceLastFrame);

	
	return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{

	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		static_cast<CEGUI::Key::Scan> (e.key));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);

	// Transici¨®n al siguiente estado.
	// Espacio --> PlayState


	if (!_credits && !_highscore && e.key == OIS::KC_Z) {
		_exitGame = true;
	}
	if (_credits && e.key == OIS::KC_ESCAPE) {

		exitButton->setVisible(true);
		playButton->setVisible(true);
		highscoreButton->setVisible(true);
		creditsButton->setVisible(true);
		//pacmanTittle->setVisible(true);
		fondoCredits->setVisible(false);
		fondoScore->setVisible(false);
		_credits = false;

	}
	if (e.key == OIS::KC_ESCAPE && _highscore) {

		introStateUI->setVisible(true);
		exitButton->setVisible(true);
		playButton->setVisible(true);
		highscoreButton->setVisible(true);
		creditsButton->setVisible(true);
		//pacmanTittle->setVisible(true);
		fondoCredits->setVisible(false);
		fondoScore->setVisible(false);
		_highscore = false;

	}

}

void
IntroState::keyReleased
(const OIS::KeyEvent &e)
{


	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		static_cast<CEGUI::Key::Scan> (e.key));
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		e.state.X.rel, e.state.Y.rel);
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
		convertMouseButton(id));

	
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/CursorPulsado");
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
		convertMouseButton(id));
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(
		"TaharezLook/Cursor");
}

IntroState*
IntroState::getSingletonPtr()
{
	return msSingleton;
}

IntroState&
IntroState::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}

bool IntroState::play(const CEGUI::EventArgs &e) {

	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	changeState(PlayState::getSingletonPtr());

	return true;
}
bool IntroState::quit(const CEGUI::EventArgs &e) {
	_exitGame = true;
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
	return true;
}
bool IntroState::highscore(const CEGUI::EventArgs &e) {

	_highscore = true;
	instruccionesButton->setVisible(false);
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	//pacmanTittle->setVisible(false);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(true);
	fondoInstrucciones->setVisible(false);

	/*
	std::ifstream scoreFile;
	scoreFile.open("scores.txt", std::ifstream::in);
	std::stringstream scores;
	std::string scoreResult;
	std::pair<int, std::string> pair;
	std::vector<std::pair<int, std::string>> vectorPairs;
	
	while (std::getline(scoreFile, scoreResult)){
		std::string name = "";
		int score = 0;

		name = scoreResult.substr(0, scoreResult.find("/", 0));
		score = atoi(scoreResult.substr(scoreResult.find("/", 0) + 1, scoreResult.length()).c_str());
		pair = std::pair<int, std::string>(score, name);
		vectorPairs.push_back(pair);
	}


	scoreFile.close();

	for (std::pair<int, std::string> p : vectorPairs)
	{
		scores << p.second << "................................................ " << p.first << "\n";
	}

	_scoreText->setText(scores.str());
	_scoreText->setVisible(true);
	*/
	return true;
}
bool IntroState::credits(const CEGUI::EventArgs &e) {
	_credits = true;
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	instruccionesButton->setVisible(false);

	//pacmanTittle->setVisible(false);
	fondoCredits->setVisible(true);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(false);
	/*
	_credits = true;
	_highscore = false;
	return true;
	*/
	return true;
}

bool IntroState::instrucciones(const CEGUI::EventArgs &e) {

	instruccionesButton->setVisible(false);
	exitButton->setVisible(false);
	playButton->setVisible(false);
	highscoreButton->setVisible(false);
	creditsButton->setVisible(false);
	instruccionesButton->setVisible(false);
	//pacmanTittle->setVisible(false);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(true);

	return true;
}
bool IntroState::atras(const CEGUI::EventArgs &e) {

	exitButton->setVisible(true);
	playButton->setVisible(true);
	highscoreButton->setVisible(true);
	creditsButton->setVisible(true);
	instruccionesButton->setVisible(true);
	//pacmanTittle->setVisible(false);
	fondoCredits->setVisible(false);
	fondoScore->setVisible(false);
	fondoInstrucciones->setVisible(false);

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

	//pacmanTittle = introStateUI->getChild("PacManTittle");

	fondoCredits = introStateUI->getChild("VentanaCredits");
	fondoScore = introStateUI->getChild("VentanaScore");
	fondoInstrucciones = introStateUI->getChild("VentanaInstrucciones");

	_atrasInstrucciones = fondoInstrucciones->getChild("AtrasInstrucciones");
	_atrasInstrucciones->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));
	_atrasScores = fondoScore->getChild("AtrasScore");
	_atrasScores->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));
	_atrasCredits = fondoCredits->getChild("AtrasCredits");
	_atrasCredits->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&IntroState::atras, this));
//	_scoreText = fondoScore->getChild("scoreText");

	/*
	fondoHighScore = introStateUI->getChild("fondoHighScore");

	fondoCredits = introStateUI->getChild("fondoCredits");

	fondoHighScore->setXPosition(CEGUI::UDim(0.50, 0));

	_scoreText = fondoHighScore->getChild("scoreText");


	fondoHighScore->setVisible(false);
	fondoCredits->setVisible(false);
	*/
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