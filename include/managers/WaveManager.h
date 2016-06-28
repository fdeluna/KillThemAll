#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Map.h"
#include "Player.h"
#include "EnemyFighter.h"

#include <vector>
#include <Ogre.h>

class WaveManager : public Ogre::Singleton<WaveManager> {

public:

	WaveManager(Ogre::SceneManager* sceneManager) : _sceneManager(sceneManager){};
	~WaveManager();

	static WaveManager& getSingleton();
	static WaveManager* getSingletonPtr();

	// TODO INIT-WAVE
	void initWave();
	void wave(float deltaTime);
	void cleanWave();

	Map* getMap(){ return _map; };
	void setPlayer(Player* player);
	Ogre::Vector3 getRandomNodePosition(){ return _map->getRandomNodePosition(); };

	//Functions for resume game
	float timeGame() { return _time; }
	int levelPlayer() { return _levelGame; }
	int countBullets(){ return _bullets; };
	int countEnemies() { return _enemiesKilled; }
	int countPots() { return _pots; }
	int getWaveEnemiesKilled() { return _waveEnemiesKilled; }
	int getWaveEnemies() { return _waveEnemies; }

	void setTimeGame(float timeGame){ _time = timeGame; };
	void setCountBullets(int countBullets){ _bullets = countBullets; };
	void setCountEnemies(int countEnemies){ _waveEnemies = countEnemies; };

	void addEnemyKilled() { _enemiesKilled++;  _waveEnemiesKilled++; }

	void setLevelGun(int _level){ levelGun = _level; };
	void setLevelMines(int _level){ levelMines = _level; };
	void setLevelPots(int _level){ levelPots = _level; };

	int getLevelGun(){ return levelGun; };
	int getLevelMines(){ return levelMines; };
	int getLevelPots(){ return levelPots; };


private:

	Map* _map = nullptr;
	Ogre::SceneManager* _sceneManager;
	std::vector<EnemyFighter*> _enemies;

	float _spawnEnemy;
	Player* _player;
	float _playerCurrentLife = 0;

	float _time;
	int _bullets;
	int _maxEnemiesInMap = 20;
	int _waveEnemies = 10;
	int _waveEnemiesKilled = 0;
	int _enemiesKilled = 0;
	int _pots;

	int levelGun;
	int levelMines;
	int levelPots;
	//LevelGame
	int _levelGame = 0;
	int _numWaves = 1;

};

#endif