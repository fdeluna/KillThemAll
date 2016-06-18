#include "EnemyFighter.h"


EnemyFighter::EnemyFighter(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager)
{

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "EnemyFighter", mesh, Ogre::Vector3(0.5, 0.25, 0.5), position);
	_sceneNodeComponent->getSceneNode()->setScale(Ogre::Vector3(0.15, 0.15, 0.15));

	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::PLAYER, _sceneNodeComponent);
	addComponent(_rigidBodyComponent);

	addComponent(_sceneNodeComponent);

	//Base Stats
	level = 1; 
	life = 1;
	speed = SPEEDS[Speed::NORMAL];
	//damage = maxLifePlayer/5;//Initial value  1/5 max life player //MaxDamage 1/3 max life player
	atkVelocity = ATTACKVELOCITIES[AttackVelocity::SLOW];
	killed = false;
	hitted = false;
	enemyCollisionPlayer = false;
	timeStun = 0.0f;
	stunMax = 1.0f;
	//Initial effects
	//AudioController::getSingletonPtr()->playAudio(Audio::SPAWN);
	//Particulas creacion
	anim = _sceneNodeComponent->getEntity()->getAnimationState("my_animation");
	anim->setTimePosition(4);
	anim->setLength(8);
	//anim->setLoop(true);
	anim->setEnabled(true);
}



void EnemyFighter::levelUp(){

	level++;
	//Particulas de subida de nivel si da tiempo
	//if el level al que suben les da un incremento de stats importande como el 10 y el 15
	
	//pueden emitir una particula mas exagerada
	switch (level){

		case 10:

			speed = SPEEDS[Speed::NORMAL];
			atkVelocity = ATTACKVELOCITIES[AttackVelocity::NORMAL];

		case 15:

			speed = SPEEDS[Speed::FAST];

	
	}

	if (level % 5 == 0 && life < 6){
	
		life++;
	}

	
}

void EnemyFighter::update(const Ogre::FrameEvent& evt){
	
	anim->addTime(evt.timeSinceLastFrame);
	/*
	//CONDICIONES DE ESTADOS
	if (life <= 0){

		state = EnemyState::DIE;
		//Reproducir animacion killed o efecto de particulas killed

	}
	else if (enemyCollisionPlayer){//Si recibe colision con player
	
		state = EnemyState::ATTACK;
	}
	else if (hitted && killed == false){//si es golpeado
	
		state = EnemyState::HITTED;
		timeStun = 0;
		
	}
	else{
	
		state = EnemyState::MOVE;
	}


	//STUN
	if (timeStun < stunMax){
		canMove = false;
	}
	else{
		canMove = true;
	}
	


	//STATES
	switch (state){
	
		case EnemyState::ATTACK:

			if (canAttack){

				//Si hay animacion de atacar--->play()
				//Si hay sonido --->play()
				attack();
			}
			

		case EnemyState::MOVE:
		
			if (canMove){
			
				move();
			}
		case EnemyState::DIE:

			die();
	
		case EnemyState::HITTED:

			AudioController::getSingletonPtr()->playAudio(Audio::HITENEMY);
			//Si reibe colision con bala--->damageHit(danio bala);
	
	}




	*/

}

void EnemyFighter::die(){

	AudioController::getSingletonPtr()->playAudio(Audio::KILLENEMY);
	killed = true;
	

}
//dmg es el danio que hace el proyectil del jugador al enemigo 1

int EnemyFighter::damageHit(int dmg){

	life = life - dmg;

}

void EnemyFighter::attack(){


	//lifePlayer = lifePlayer - (int)damage;

}

void EnemyFighter::move(){

	//translate = direction * SPEER....

}