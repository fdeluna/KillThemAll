#ifndef GameManager_H
#define GameManager_H

#include <stack>
#include <Ogre.h>
#include <OgreSingleton.h>
#include <OIS/OIS.h>

#include "InputManager.h"

class GameState;

class GameManager : public Ogre::FrameListener, public Ogre::Singleton<GameManager>, public OIS::KeyListener, public OIS::MouseListener
{
 public:
  GameManager ();
  ~GameManager ();

  void start (GameState* state);
    
  void changeState (GameState* state);
  void pushState (GameState* state);
  void popState ();
    
  static GameManager& getSingleton ();
  static GameManager* getSingletonPtr ();
  InputManager* getInputManager();

 protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneManager;
  Ogre::RenderWindow* _renderWindow;

  void loadResources ();
  bool configure ();
  
  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

 private:
  bool keyPressed (const OIS::KeyEvent &e);
  bool keyReleased (const OIS::KeyEvent &e);

  bool mouseMoved (const OIS::MouseEvent &e);
  bool mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  bool mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);
    
  InputManager *_inputMgr;
 
  std::stack<GameState*> _states;
};
#endif