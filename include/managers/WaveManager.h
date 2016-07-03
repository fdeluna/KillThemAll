#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Map.h"
#include "Player.h"
#include "EnemyFighter.h"
#include "EnemyMiner.h"

#include <random>
#include <vector>
#include <Ogre.h>

class WaveManager : public Ogre::Singleton<WaveManager> {

public:
	WaveManager(Ogre::SceneManager* sceneManager) : _sceneManager(sceneManager){};
	~WaveManager(){ cleanWave(); };

	static WaveManager& getSingleton();
	static WaveManager* getSingletonPtr();
	

	void resetWaveManager();
	void initWave();
	void wave(float deltaTime);
	void cleanWave();
	void cleanEnemies();

	Map* getMap(){ return _map; };
	void setPlayer(Player* player);
	Ogre::Vector3 getRandomNodePosition(){ return _map->getRandomNodePosition(); };
				
	int countEnemies() { return _enemiesKilled; }	
	int getWaveEnemiesKilled() { return _waveEnemiesKilled; }
	int getWaveEnemies() { return _waveEnemies; }
	
	void addEnemyKilled() { _enemiesKilled++;  _waveEnemiesKilled++; }

	void setLevelGun(int level){ _levelGun = level; };
	void setLevelMines(int level){ _levelMines = level; };
	void setLevelPots(int level){ _levelPots = level; };

	int getLevelGun(){ return _levelGun; };
	int getLevelMines(){ return _levelMines; };
	int getLevelPots(){ return _levelPots; };
	
	float getGameTime(){ return _gameTime; };
	void setGameTime(float time){ _gameTime = time; };

	int getEnemiesKilled(){ return _enemiesKilled; };
	void setEnemiesKilled(float enemies){ _enemiesKilled = enemies; };

	int getBulletsUsed(){ return _bulletsUsed; };
	void setBulletUsed(float bullets){ _bulletsUsed = bullets; };

	int getMinesUsed(){ return _minesUsed; };
	void setMinesUsed(float mines){ _minesUsed = mines; };

	int getPotsUsed(){ return _potsUsed; };
	void setPotsUsed(float pots){ _potsUsed = pots; };

	int getLevel(){ return _levelGame; };

private:	
	Map* _map = nullptr;
	Ogre::SceneManager* _sceneManager;
	std::vector<Enemy*> _enemies;

	float _spawnEnemy;
	Player* _player;
	float _playerCurrentLife = 0;

	float _time;
	int _bullets;	
	int _waveEnemies = 5;
	int _waveEnemiesKilled = 0;
	int _enemiesKilled = 0;	
	int _levelGun;
	int _levelMines;
	int _levelPots;
	
	int _levelGame = 0;
	int _numWaves = 1;
	
	float _gameTime;
	int _minesUsed;
	int _bulletsUsed;
	int _potsUsed;
};
#endif