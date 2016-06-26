#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerInputComponent.h"
#include "Enum.h"
#include "AudioController.h"

class Player : public GameObject{

public:
	Player() : _sceneNodeComponent(nullptr), _rigidBodyComponent(nullptr), _playerInput(nullptr){};
	Player(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);
	~Player();

	void collision(GameObject* gameObject);

	Ogre::Vector3 getPosition(){ return _rigidBodyComponent->getPosition(); };
	SceneNodeComponent* getSceneNodeComponent(){ return _sceneNodeComponent; };
	PlayerInputComponent* getPlayerInputComponent(){ return _playerInput; };
	
	

	int getLife(){ return life; };
	int setLife(int hp){ life = hp; };
	int getLevel(){ return level; };
	void setLevel(int levelPlayer){ level = levelPlayer; };
	int getPotions(){ return numPots; };
	int setPotions(int pots){ numPots = pots; };
	int getPotionsCount(){ return countPots; };
	bool getMineActive(){ return mineActive; };
	void setMineActive(bool active){ mineActive = active; };
	int getCountMines(){ return numMines; };
	void setCountMines(int mines){ numMines = mines; };
	void setLevelMines(int _mines){ levelMine = _mines; };
	void setLevelPots(int _pots){ levelPotion = _pots; };
	int getLevelMines(){ return levelMine; };
	int getLevelPots(){ return levelPotion; };

	Ogre::String getTextDie(){ return textDie; };

	//FUNTIONS
	bool die();
	void hitted(int damage);
	void levelUp();
	void levelUpPotion();
	void levelUpMines();
	void potion();

private:


private:
	SceneNodeComponent* _sceneNodeComponent;
	RigidBodyComponent* _rigidBodyComponent;
	PlayerInputComponent* _playerInput;
	AudioController* audioController;

	Ogre::String textDie;
	int lifeMax = 8;
	int life = 8;
	int level = 1;
	//POTS
	int numPots = 1;
	int numPotsMax = 1;
	int countPots = 0;				
	int levelPotion = 1;
	//MINES
	int mineActive = false;
	int numMines = 1;
	int numMinesMax = 1;
	int levelMine = 1;
	float velMove = SPEEDPLAYER[SpeedPlayer::SLOWP];
};

#endif