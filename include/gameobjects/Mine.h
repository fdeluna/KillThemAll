#ifndef Mine_H
#define Mine_H

#include "Player.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "AudioController.h"

using namespace Ogre;

class Mine : public GameObject
{
public:
	Mine() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Mine(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, GameObjectType type);
	~Mine();

	void update(float deltaTime);
	void active(){ _activeMine = true; };
	void shoot();

protected:

	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	AudioController* audioController;	
	
	Player* _player;
	bool _activeMine = false;
	bool explosion = false;
	float timeExplote = 2.5;
	float timeDestroy = 0.25;
	float timer = 0;
	
};
#endif
