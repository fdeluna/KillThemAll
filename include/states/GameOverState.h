#ifndef GameOverState_H
#define GameOverState_H


#include "GameState.h"
#include "Map.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>
#include "AudioController.h"

class GameOverState : public Ogre::Singleton<GameOverState>, public GameState
{
public:
	GameOverState(){};
	~GameOverState(){};
	static GameOverState& getSingleton();
	static GameOverState* getSingletonPtr();

	void enter();
	void exit();
	void pause();
	void resume();

	void keyPressed(const OIS::KeyEvent &e);
	void keyReleased(const OIS::KeyEvent &e);
	void mouseMoved(const OIS::MouseEvent &e);
	void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool frameStarted(const Ogre::FrameEvent &e);
	bool frameEnded(const Ogre::FrameEvent &e);

	CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);

	void createGUI();
	void checkScore();
	void statScore();

private:
	Ogre::Root *_root;
	Ogre::SceneManager *_sceneMgr;
	Ogre::Camera *_camera;
	Ogre::Viewport *_viewport;
	AudioController* audioController;
	bool _exitGame;

	CEGUI::OgreRenderer* _renderer;

	Map* _Map;
	// CEGUI


	bool quit(const CEGUI::EventArgs &e);
	bool upgrade(const CEGUI::EventArgs &e);
	bool ready(const CEGUI::EventArgs &e);
	bool upgradeWeapon(const CEGUI::EventArgs &e);

	//ANTIGUAS
	CEGUI::Window* _GameOverStateUI;
	CEGUI::Window* _gameOverUI;
	CEGUI::Window* _winUI;
	CEGUI::Window* _exitGameOver;
	CEGUI::Window* _scoreText;
	CEGUI::Window* _scoreTextLose;
	CEGUI::Window* _getReadyText;
	CEGUI::Window* _scoreTextGUI;
	CEGUI::Window* _scoreNumberTextGUI;
	CEGUI::Window* _lifeText;
	CEGUI::Window*	_nameText;
	CEGUI::Window*	_nameTextLose;
	CEGUI::Window* _saveGameOver;
	CEGUI::Window* _saveWin;
	CEGUI::Window* _heart1;
	CEGUI::Window* _heart2;
	CEGUI::Window* _heart3;
	CEGUI::Window* _turnText;

	//NUEVAS
	CEGUI::Window* _ventanaUpgrade;
	CEGUI::Window* _ventanaGameOver;
	CEGUI::Window* _ready;
	CEGUI::Window* _upgrade;
	CEGUI::Window* _upgradeClub;
	CEGUI::Window* _upgradeGun;
	CEGUI::Window* _upgradeShotGun;
	CEGUI::Window* _timeGame;
	CEGUI::Window* _level;
	CEGUI::Window* _enemies;
	CEGUI::Window* _boss;
	CEGUI::Window* _bullets;
	CEGUI::Window* _pots;

	CEGUI::Window* _exit;
	float sizeX = 0.15;
	// Time match for cegui GUI
	float _time = 0;

};

#endif
