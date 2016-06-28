#ifndef PlayState_H
#define PlayState_H

#include "GameState.h"
#include "WaveCompleteState.h"
#include "GameOverState.h"
#include "PhysicsManager.h"

#include "PathFinder.h"
#include "Player.h"
#include "Bullet.h"
#include "Gun.h"
#include "EnemyFighter.h"
#include "Mine.h"

#include <future>
#include <algorithm>
#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>
#include "AudioController.h"


class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
	PlayState(){};
	~PlayState(){};
	static PlayState& getSingleton();
	static PlayState* getSingletonPtr();

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
	void printTextGUI();
	void updateLevelWeapons();
private:	
	Ogre::Root *_root;
	Ogre::SceneManager *_sceneMgr;
	Ogre::Camera *_camera;
	Ogre::Viewport *_viewport;
	AudioController* audioController;
	bool _exitGame;

	float _deltaT = 0;
	bool can = true;

	float _gameOverDelay = 0;
	float _startDelay = 0;
	
	float timer = 0;
	float timerReload = 0;
	WaveManager* _waveManager;
	PhysicsManager* _physicsManager;
	PathFinder* _pathFinder;	
	Player* _player;	

	Bullet* _bullet;
	Gun* _gun;
	Mine* _mine;	

	// CEGUI
	bool quit(const CEGUI::EventArgs &e);
	bool save(const CEGUI::EventArgs &e);
	void hudLife();

	
	//ANTIGUAS
	CEGUI::Window* playStateUI;
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

	CEGUI::Window* _vida1;
	CEGUI::Window* _vida2;
	CEGUI::Window* _vida3;
	CEGUI::Window* _vida4;
	CEGUI::Window* _vida5;
	CEGUI::Window* _vida6;
	CEGUI::Window* _vida7;
	CEGUI::Window* _vida8;

	CEGUI::Window* _turnText;
	 
	CEGUI::Window* _wave;
	CEGUI::Window* _enemies;
	CEGUI::Window* _bulletsGUI;
	CEGUI::Window* _minesGUI;
	CEGUI::Window* _potGUI;
	CEGUI::Window* _centralText;
	CEGUI::Window* _levelText;
	CEGUI::Window* _warning;

	bool activeWarning = false;
	float timerWarning = 0;

	
	int enemiesNextWave =0;

	//NUEVAS
	CEGUI::Window* _hud;
	CEGUI::Window* _hudLife;
	CEGUI::Window* _hudWeapons;
	CEGUI::Window* _hudWeaponsClub;
	CEGUI::Window* _hudWeaponsGun;
	CEGUI::Window* _hudWeaponsShotGun;
	// Time match for cegui GUI
	float _time = 0;

};

#endif
