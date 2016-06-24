#include "Player.h"

Player::Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh) : GameObject(sceneManager){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Player", mesh, Ogre::Vector3(0.02, 0.02, 0.02), position);
		
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::PLAYER, _sceneNodeComponent);
	_playerInput = new PlayerInputComponent(_rigidBodyComponent, _sceneManager);
	_type = GameObjectType::PLAYER;
	Ogre::Camera* cam = _sceneManager->getCamera("PlayState");	
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);
	addComponent(_playerInput);
	audioController = AudioController::getSingletonPtr();
}

Player::~Player(){
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	delete _playerInput;
	GameObject::~GameObject();
}


void Player::collision(GameObject* gameObject){
	if (gameObject){	
		if (gameObject->getType() == GameObjectType::HELL){			
				life = 0;			
		}
	}
}

bool Player::die(){

	
	if(life <= 0){
		return true;
	}
	else{
		return false;
	}
}

void Player::hitted(int damage){

	life = life - damage;

}

void Player::potion(){

	if (numPots > 0){
		life = lifeMax;
		numPots--;
		//Resume Game
		countPots++;
	}

}

void Player::levelUp(){

	level++;

	std::cout << level << "PLAYER LEVEL" << std::endl;
	switch (level){
		

	case 5:
		_playerInput->setSpeedPlayer(SPEEDPLAYER[SpeedPlayer::NORMALP]);
		numPots = numPotsMax;
		numMines = numMinesMax;
	case 10:
		
		_playerInput->setSpeedPlayer(SPEEDPLAYER[SpeedPlayer::FASTP]);
		numPots = numPotsMax;
		numMines = numMinesMax;


	default:
		break;
	}
	

}
void Player::levelUpPotion(){

	levelPotion++;
	std::cout << level << "PLAYER POTION" << std::endl;

	switch (levelPotion){
	
		case 2:

			numPotsMax = 2;
			
		case 3:

			numPotsMax = 3;

		default:
			break;

	}

}
void Player::levelUpMines(){

	levelMine++;
	std::cout << level << "PLAYER MINE" << std::endl;

	switch (levelMine){

	case 2:

		numMinesMax = 2;

	case 3:

		numMinesMax = 3;

	default:
		break;

	}

}
