
#ifndef WaveManager_H
#define WaveManager_H

#include <Ogre.h>
#include "OgreSingleton.h"
#include "Player.h"
#include <OIS/OIS.h>

class WaveManager : public Ogre::Singleton<WaveManager>
{
public: 
	WaveManager();
	~WaveManager();

	// Heredados de Ogre::Singleton.
	static WaveManager& getSingleton();
	static WaveManager* getSingletonPtr();

	void wave();

	//Functions for resume game
	float timeGame();
	int levelPlayer();
	int countBullets();
	int countEnemies();
	int countBoss();
	int countPots();

	void setTimeGame(float timeGame){time = timeGame; };
	void setLevelPlayer(int levelPlayer){ level = levelPlayer; };
	void setCountBullets(int countBullets){ bullets = countBullets; };
	void setCountEnemies(int countEnemies){ enemies = countEnemies; };
	void setCountBoss(int countBoss){ boss = countBoss; };
	void setCountPots(int countPots){ pots = countPots; };

protected:

	float time;
	int level;
	int bullets;
	int enemies;
	int boss;
	int pots;

	//LevelGame
	int levelGame = 1;
	int numWaves = 1;
	
};

#endif