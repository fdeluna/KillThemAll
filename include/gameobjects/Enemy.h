#ifndef ENEMY_H
#define ENEMY_H

#include "Node.h"
#include "Player.h"
#include "EnemyPathFinderComponent.h"

class Enemy : public GameObject{

public:
	Enemy() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _pathFinderComponent(nullptr){};
	Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh,Player* player);
	virtual ~Enemy();

	virtual void update(float deltaTime);
	virtual void collision(GameObject* gameObject){};

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };
	
	void levelUp();
	//Tiene qye haber una funcion que haga subir d enivel a los mounstros
	//levelUp() que lo hace de manera individual, pero luego tiene que haber una funcion en el play state
	//que elegira usar levelUp() segun la oleada en la que estemos.
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


protected:	
	Player* _player;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;
	EnemyState _state;
	
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
	bool killed;//Indica si esta muerto
	bool hitted;//Indica si ha sido daniado
	
	bool attackDistance();	

	virtual void move(float deltaTime);
	virtual bool attack(float deltaTime) { return true; };
	virtual void die(float deltaTime) {};
	virtual void hitted(float deltaTime) {};
};




#endif