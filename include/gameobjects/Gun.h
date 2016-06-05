#ifndef Gun_H
#define Gun_H


#include "Weapon.h"

using namespace Ogre;

class Gun : public Weapon
{
public:

	//CONSTRUCTOR
	Gun();
	//Gun(SceneManager* sceneManager, std::string mesh, String nodeName, Vector3 position);
	//DESTRUCTOR
	~Gun();

	void upgrade();

protected:

	
};

#endif