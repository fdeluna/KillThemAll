#ifndef Weapon_H
#define Weapon_H

#include "GameObject.h"
#include "AudioController.h"
#include "Bullet.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"

using namespace Ogre;

class Weapon : public GameObject
{
public:

	//CONSTRUCTOR
	Weapon() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr){};
	Weapon(SceneManager* sceneManager, std::string mesh, String nodeName, Vector3 position);
	//DESTRUCTOR
	//~Weapon();

	 void update(const Ogre::FrameEvent& evt);

	void shoot();
	void upgrade();
	//GETTERS/SETTERS
	int getMaxAmmo();
	void setMaxAmmo(int ammo);

	float getCadence();
	void setCadence(float timeCadence);



protected:

	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;

	//VARIABLES
	int power;
	int maxAmmo;//en un principio son balas infinitas pero por si a caso
	CadenceWeapon cadence;
	ScopeWeapon scope;
	int level;//nivel del arma

	Bullet* bullet;//cada arma guarda las balas que dispara
	std::vector<Bullet*> bullets;

	//CONTROL
	
	//EFFECTS	
	//Sound sound
	//Particles....
};

#endif