#ifndef WaveCompleteState_H
#define WaveCompleteState_H


#include "AudioManager.h"
#include "GameState.h"
#include "Map.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>

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
	AudioManager* AudioManager;	
	
	int levelGun = 1;
	int levelMines = 1;
	int levelPots = 1;

	bool quit(const CEGUI::EventArgs &e);
	bool upgrade(const CEGUI::EventArgs &e);
	bool ready(const CEGUI::EventArgs &e);
	bool upgradeGun(const CEGUI::EventArgs &e);
	bool upgradeMines(const CEGUI::EventArgs &e);
	bool upgradePots(const CEGUI::EventArgs &e);
	
	CEGUI::Window* _waveCompleteStateUI;	
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
		
	float _time = 0;
};

#endif
