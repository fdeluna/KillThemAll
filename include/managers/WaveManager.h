#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Map.h"
#include "Player.h"
#include "EnemyFighter.h"

#include <vector>
#include <Ogre.h>

class WaveManager : public Ogre::Singleton<WaveManager> {

public:

	WaveManager(Ogre::SceneManager* sceneManager);
	~WaveManager();

	static WaveManager& getSingleton();
	static WaveManager* getSingletonPtr();

	// TODO INIT-WAVE
	void wave(float deltaTime);

	Map* getMap(){ return _map; };
	void setPlayer(Player* player){ _player = player; };

	//Functions for resume game
	float timeGame();
	int levelPlayer();
	int countBullets();
	int countEnemies();
	int countBoss();
	int countPots();

	void setTimeGame(float timeGame){ _time = timeGame; };
	void setLevelPlayer(int levelPlayer){ _level = levelPlayer; };
	void setCountBullets(int countBullets){ _bullets = countBullets; };
	void setCountEnemies(int countEnemies){ _enemies = countEnemies; };
	void setCountBoss(int countBoss){ _boss = countBoss; };
	void setCountPots(int countPots){ _pots = countPots; };

private:

	Map* _map;
	Ogre::SceneManager* _sceneManager;

	std::vector<EnemyFighter*> enemies;
	float _spawnEnemy;
	Player* _player;

	
	float _time;
	int _level;
	int _bullets;
	int _enemies;
	int _boss;
	int _pots;

	//LevelGame
	int _levelGame = 1;
	int _numWaves = 1;

};

#endif