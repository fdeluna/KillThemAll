#include <Ogre.h>

#include "GameManager.h"
#include "GameState.h"

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;

GameManager::GameManager()
{
	_root = 0;
}

GameManager::~GameManager()
{
	while (!_states.empty()) {
		_states.top()->exit();
		_states.pop();
	}

	if (_root)
		delete _root;
}
InputManager* GameManager::getInputManager()
{
	return _inputMgr;
}
void
GameManager::start
(GameState* state)
{	
	_root = new Ogre::Root();

	loadResources();

	if (!configure())
		return;

	_inputMgr = new InputManager;
	_inputMgr->initialise(_renderWindow);
	
	_inputMgr->addKeyListener(this, "GameManager");
	_inputMgr->addMouseListener(this, "GameManager");	
	
	_root->addFrameListener(this);
	
	changeState(state);
	
	_root->startRendering();
}

void
GameManager::changeState
(GameState* state)
{	
	if (!_states.empty()) 
	{		
		_states.top()->exit();		
		_states.pop();
	}
	
	_states.push(state);
	_states.top()->enter();
}

void
GameManager::pushState
(GameState* state)
{	
	if (!_states.empty())
		_states.top()->pause();
	
	_states.push(state);	
	_states.top()->enter();
}

void
GameManager::popState()
{	
	if (!_states.empty()) 
	{
		_states.top()->exit();
		_states.pop();
	}
	
	if (!_states.empty())
		_states.top()->resume();
}

void
GameManager::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
	Ogre::String sectionstr, typestr, datastr;
	while (sI.hasMoreElements()) {
		sectionstr = sI.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typestr = i->first;    datastr = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation
				(datastr, typestr, sectionstr);
		}
	}
}

bool
GameManager::configure()
{
	if (!_root->restoreConfig()) {
		if (!_root->showConfigDialog()) {
			return false;
		}
	}
	_renderWindow = _root->initialise(true, "My render window");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return true;
}

GameManager*
GameManager::getSingletonPtr()
{
	return msSingleton;
}

GameManager&
GameManager::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}

bool
GameManager::frameStarted
(const Ogre::FrameEvent& evt)
{
	_inputMgr->capture();

	return _states.top()->frameStarted(evt);
}

bool
GameManager::frameEnded
(const Ogre::FrameEvent& evt)
{
	return _states.top()->frameEnded(evt);
}

bool
GameManager::keyPressed
(const OIS::KeyEvent &e)
{
	_states.top()->keyPressed(e);
	return true;
}

bool
GameManager::keyReleased
(const OIS::KeyEvent &e)
{
	_states.top()->keyReleased(e);
	return true;
}

bool
GameManager::mouseMoved
(const OIS::MouseEvent &e)
{
	_states.top()->mouseMoved(e);
	return true;
}

bool
GameManager::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	_states.top()->mousePressed(e, id);
	return true;
}

bool
GameManager::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	_states.top()->mouseReleased(e, id);
	return true;
}