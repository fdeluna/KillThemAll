#ifndef WaveCompleteState_H
#define WaveCompleteState_H


#include "GameState.h"
#include "Map.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>
#include "AudioController.h"

class WaveCompleteState : public Ogre::Singleton<WaveCompleteState>, public GameState
{
public:
	WaveCompleteState(){};
	~WaveCompleteState(){};
	static WaveCompleteState& getSingleton();
	static WaveCompleteState* getSingletonPtr();

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
	void resetLevelGun(){ levelGun = 1; };
	void resetLevelMines(){ levelMines = 1; };
	void resetLevelPots(){ levelPots = 1; };
	int getLevelGun(){ return levelGun; };
	int getLevelMines(){ return levelMines; };
	int getLevelPots(){ return levelPots; };

	CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);

	void createGUI();

private:
	Ogre::Root *_root;
	Ogre::SceneManager *_sceneMgr;
	Ogre::Camera *_camera;
	Ogre::Viewport *_viewport;
	AudioController* audioController;
	bool _exitGame;


	CEGUI::OgreRenderer* _renderer;

	Map* _Map;
	//Weapons
	int levelGun = 1;
	int levelMines = 1;
	int levelPots = 1;

	// CEGUI


	bool quit(const CEGUI::EventArgs &e);
	bool upgrade(const CEGUI::EventArgs &e);
	bool ready(const CEGUI::EventArgs &e);
	bool upgradeGun(const CEGUI::EventArgs &e);
	bool upgradeMines(const CEGUI::EventArgs &e);
	bool upgradePots(const CEGUI::EventArgs &e);

	//ANTIGUAS
	CEGUI::Window* _waveCompleteStateUI;
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
	CEGUI::Window* _ventanaWaveComplete;
	CEGUI::Window* _ready;
	CEGUI::Window* _upgrade;
	CEGUI::Window* _upgradeClub;
	CEGUI::Window* _upgradeGun;
	CEGUI::Window* _upgradeShotGun;

	CEGUI::Window* _upgradeClubInfo;
	CEGUI::Window* _upgradeGunInfo;
	CEGUI::Window* _upgradeShotGunInfo;


	CEGUI::Window* _exit;
	
	// Time match for cegui GUI
	float _time = 0;

};

#endif
