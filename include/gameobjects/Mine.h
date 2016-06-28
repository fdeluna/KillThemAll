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
	Mine(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Mine();

	void update(const Ogre::FrameEvent& evt);
	void shoot();
	void collision(GameObject* gameObject);


	//GETTER/SETTERS
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	RigidBodyComponent* getRigidBodyComponent(){ return _rigidBodyComponent; };

	void setAutomaticExplosion(bool explosion){ automaticExplosion = explosion; };
	float getTimer(){ return timer; };

	bool isActive(){ return _active; };
	void setActive(bool active){ _active = active; };
protected:

	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	AudioController* audioController;
	//Particles
	Ogre::ParticleSystem* partSystem;
	SceneNode* nodeParticle;
	float timeParticle;

	int numBullet;
	Player* _player;
	float timeExplote = 5;
	float timer = 0;
	bool explosion = false;
	float timeDestroy = 1;
	bool automaticExplosion = false;
};
#endif
