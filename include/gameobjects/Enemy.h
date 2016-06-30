#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "EnemyPathFinderComponent.h"
#include "AudioController.h"

class Enemy : public GameObject{

public:
	Enemy() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _pathFinderComponent(nullptr){};
	Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh,Player* player,int level);
	virtual ~Enemy();

	virtual void update(float deltaTime);
	virtual void collision(GameObject* gameObject){};

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };
	
	virtual void levelUp(){};

	virtual void move(float deltaTime){};
	virtual bool attack(float deltaTime) { return true; };
	virtual void die(float deltaTime) {};
	virtual void hitted(float deltaTime);


	//Tiene qye haber una funcion que haga subir d enivel a los mounstros
	//levelUp() que lo hace de manera individual, pero luego tiene que haber una funcion en el play state
	//que elegira usar levelUp() segun la oleada en la que estemos.
	void damageHit(int dmg) { _life -= dmg;}//	
	
	//Getters/Setters
	int getLife() { return _life; }
	void setLife(int hp){ _life = hp; };

	float getSpeed() { return _speed; }
	void setSpeed(float spd){ _speed = spd; };

	float getDamage() { return _damage; }
	void setDamage(float atk){ _damage = atk; };


	float getAtkVelocity() { return atkVelocity; }
	void setAtkVelocity(float atkVel){ atkVelocity = atkVel; };


protected:	
	Player* _player;
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	EnemyPathFinderComponent* _pathFinderComponent;
	EnemyState _state;
	AudioController* audioController;
	
	//Variables
	int _life = 1;//vida del enemigo
	float _speed = 3;//velocidad de movimiento del enemigo
	float _damage = 1;//Danio que hace el enemigo
	float atkVelocity;//velocidad de ataque del enemigo
	int _level;//Nivel del enemigo
	float _timeStun = 0;//Contador para stun
	float _stunMax = 1;//Tiempo que se queda quieto tras recibir un golpe
	
	//Control	
	bool isAttacking = false;	
	bool killed;//Indica si esta muerto	
	
	bool attackDistance();	
};




#endif