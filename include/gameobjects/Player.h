#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerInputComponent.h"
#include "Enum.h"
#include "AudioManager.h"

class Player : public GameObject{

public:
	Player() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _playerInput(nullptr){};
	Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Player();

	void collision(GameObject* gameObject);

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	PlayerInputComponent* getPlayerInputComponent(){ return _playerInput; };
	
	
	int getMaxLife() { return _lifeMax; };
	int getLife(){ return _life; };
	void setLife(int hp){ _life = hp; };
	int getLevel(){ return _level; };
	void setLevel(int levelPlayer){ _level = levelPlayer; };
	int getPotions(){ return _numPots; };
	int setPotions(int pots){ _numPots = pots; };
	int getPotionsCount(){ return _countPots; };
	bool getMineActive(){ return _mineActive; };
	void setMineActive(bool active){ _mineActive = active; };
	int getCountMines(){ return _numMines; };
	void setCountMines(int mines){ _numMines = mines; };
	void setLevelMines(int _mines){ _levelMine = _mines; };
	void setLevelPots(int _pots){ _levelPotion = _pots; };
	int getLevelMines(){ return _levelMine; };
	int getLevelPots(){ return _levelPotion; };

	Ogre::String getTextDie(){ return _textDie; };
	
	void hitted(int damage);
	void levelUp();
	void levelUpPotion();
	void levelUpMines();
	void potion();	

private:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	PlayerInputComponent* _playerInput;
	AudioManager* _audioManager;

	Ogre::String _textDie;
	int _lifeMax = 8;
	int _life = 8;
	int _level = 1;
	
	int _numPots = 1;
	int _numPotsMax = 1;
	int _countPots = 0;				
	int _levelPotion = 1;
	
	int _mineActive = false;
	int _numMines = 1;
	int _numMinesMax = 1;
	int _levelMine = 1;
	float _velMove = SPEEDPLAYER[SpeedPlayer::SLOWP];
};

#endif