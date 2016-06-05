#ifndef ENEMY_H
#define ENEMY_h

//#include <Ogre.h>

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "AudioController.h"
class Enemy : public GameObject{

public:
	Enemy(){};
	//~Enemy();

	void update(const Ogre::FrameEvent& evt);

	void setScale(Ogre::Vector3 scale);

	//Funtions
	void levelUp();
	//Tiene qye haber una funcion que haga subir d enivel a los mounstros
	//levelUp() que lo hace de manera individual, pero luego tiene que haber una funcion en el play state
	//que elegira usar levelUp() segun la oleada en la que estemos.
	void die();
	void attack();
	void move();
	int damageHit(int dmg);//Danio qu erecibe de un hit

	//Getters/Setters
	int getLife() { return life; }
	void setLife(int hp){ life = hp; };

	float getSpeed() { return speed; }
	void setSpeed(float spd){ speed = spd; };

	float getDamage() { return damage; }
	void setDamage(float atk){ damage = atk; };


	float getAtkVelocity() { return atkVelocity; }
	void setAtkVelocity(float atkVel){ atkVelocity = atkVel; };

	bool getHitted(){ return hitted; }
	void setHitted(bool hit){ hitted = hit; };

	bool getCollisionWithPlayer(){ return enemyCollisionPlayer; }
	void setCollisionWithPlayer(bool collision){ enemyCollisionPlayer = collision; };

protected:

	
	//Variables
	int life;//vida del enemigo
	float speed;//velocidad de movimiento del enemigo
	float damage;//Danio que hace el enemigo
	float atkVelocity;//velocidad de ataque del enemigo
	int level;//Nivel del enemigo
	float timeStun = 0;//Contador para stun
	float stunMax = 0;//Tiempo que se queda quieto tras recibir un golpe

	//Control
	bool canAttack = true;
	bool canMove = true;
	EnemyState state;//estado del enemigo
	bool killed;//Indica si esta muerto
	bool hitted;//Indica si ha sido daniado
	bool enemyCollisionPlayer;//Indica si ha colisionado con el player

	//Move
	Ogre::Vector3 direction;

	//Effects Variables()
	Ogre::ParticleSystem* partSystem;//Particulas para las subidas de nivel, hit de danio y morir
	Ogre::SceneNode* nodeParticle;
	float timeParticle;
	//Faltan los sonidos
};

#endif