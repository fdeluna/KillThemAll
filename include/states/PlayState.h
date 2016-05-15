#ifndef PlayState_H
#define PlayState_H


#include "GameState.h"
#include "MapGenerator.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>


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

private:	
	Ogre::Root *_root;
	Ogre::SceneManager *_sceneMgr;
	Ogre::Camera *_camera;
	Ogre::Viewport *_viewport;
	bool _exitGame;

	CEGUI::OgreRenderer* _renderer;

	MapGenerator* _mapGenerator;

};

#endif
