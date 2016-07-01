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
	_audioManager = AudioManager::getSingletonPtr();
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
			_life = 0;
			_textDie = "You fell into the hell";
		}

		if (gameObject->getType() == GameObjectType::MINES || gameObject->getType() == GameObjectType::MINEENEMY){
			_life = 0;
			_textDie = "You exploted in 100 pieces";
		}

		if (gameObject->getType() == GameObjectType::ENEMYFIGHTER){
			_textDie = "You was killed by noob enemy. . .";
		}
	}

}

void Player::hitted(int damage){

	_life -= damage;

}

void Player::potion(){
	if (_numPots > 0){
		_life = _lifeMax;
		_numPots--;		
		_countPots++;
	}

}

void Player::levelUp(){

	_level++;
	switch (_level){
	case 5:
		_playerInput->setSpeedPlayer(SPEEDPLAYER[SpeedPlayer::NORMALP]);
		_numPots = _numPotsMax;
		_numMines = _numMinesMax;
		break;
	case 10:
		_playerInput->setSpeedPlayer(SPEEDPLAYER[SpeedPlayer::FASTP]);
		_numPots = _numPotsMax;
		_numMines = _numMinesMax;
		break;
	}


}
void Player::levelUpPotion(){

	if (_levelPotion == 2){
		_numPotsMax = 2;
		_numPots = _numPotsMax;
	}
	else if (_levelPotion == 3){
		_numPotsMax = 3;
		_numPots = _numPotsMax;
	}

}
void Player::levelUpMines(){

	if (_levelMine == 2){
		_numMinesMax = 2;
		_numMines = _numMinesMax;

	}
	else if (_levelMine == 3){

		_numMinesMax = 3;
		_numMines = _numMinesMax;
	}
}
