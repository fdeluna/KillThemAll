
#ifndef IntroState_H
#define IntroState_H

#include "GameState.h"
#include "Map.h"
#include "PhysicsManager.h"
#include "AudioManager.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class IntroState : public Ogre::Singleton<IntroState>, public GameState
{
public:

	IntroState() {}

	void enter();
	void exit();
	void pause();
	void resume();

	void keyPressed(const OIS::KeyEvent &e);
	void keyReleased(const OIS::KeyEvent &e);

	void mouseMoved(const OIS::MouseEvent &e);
	void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	
	static IntroState& getSingleton();
	static IntroState* getSingletonPtr();

private:
	Ogre::Root* _root;
	Ogre::SceneManager* _sceneMgr;
	Ogre::Viewport* _viewport;
	Ogre::Camera* _camera;
	
	bool _exitGame;
	bool _play;
	bool _highscore;
	bool _credits;
	float _timeSinceLastFrame;

	bool play(const CEGUI::EventArgs &e);
	bool quit(const CEGUI::EventArgs &e);
	bool highscore(const CEGUI::EventArgs &e);
	bool credits(const CEGUI::EventArgs &e);
	bool instrucciones(const CEGUI::EventArgs &e);
	bool atras(const CEGUI::EventArgs &e);
	bool control(const CEGUI::EventArgs &e);
	bool tutorial(const CEGUI::EventArgs &e);

	void createGUI();
	
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* introStateUI;
	CEGUI::Window* exitButton;
	CEGUI::Window* playButton;
	CEGUI::Window* instruccionesButton;
	CEGUI::Window* highscoreButton;
	CEGUI::Window* creditsButton;
	CEGUI::Window* pacmanTittle;
	CEGUI::Window* fondoCredits;
	CEGUI::Window* fondoScore;
	CEGUI::Window* fondoInstrucciones;
	CEGUI::Window* select;
	CEGUI::Window* intro;
	CEGUI::Window* _scoreText;
	CEGUI::Window* _atrasCredits;
	CEGUI::Window* _atrasScores;
	CEGUI::Window* _atrasInstrucciones;
	CEGUI::Window* _control;
	CEGUI::Window* _tutorial;
	CEGUI::Window* _controlText;
	CEGUI::Window* _tutorialText;
	CEGUI::Window* _highScoreText;
	CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);

	Map* _map;
	PhysicsManager* _physicsManager;
	AudioManager* _audioManager;
};

#endif
