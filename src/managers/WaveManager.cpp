#include "WaveManager.h"

template<> WaveManager* Ogre::Singleton<WaveManager>::msSingleton = 0;

WaveManager* WaveManager::getSingletonPtr() {
	return msSingleton;
}

WaveManager& WaveManager::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}

WaveManager::WaveManager(Ogre::SceneManager* sceneManager) : _sceneManager(sceneManager)
{
	_map = new Map(_sceneManager);
	_map->GenerateMap();
}

void WaveManager::wave(float deltaTime)
{	
	_spawnEnemy += deltaTime;
	if (_spawnEnemy >= 1){
		_spawnEnemy = 0;
		EnemyFighter* newEnemy = nullptr;
		Ogre::Vector3 enemyPosition = _map->getRandomNodePosition();
		int enemyType = (rand() % 10) + 1;

		if (enemyType > 2) {
			newEnemy = new EnemyFighter(_sceneManager, Ogre::Vector3(enemyPosition.x + 0.5, 0.5, enemyPosition.z +0.5), MESHES[MeshName::ENEMYFIGHTER], _player);
			enemies.push_back(newEnemy);
		}				
	}

	if (enemies.size() > 0){
		for (int i = 0; i < enemies.size(); i++){
			if (enemies[i] && enemies[i]->isActive()){
				enemies[i]->update(deltaTime);
			}
			else{
				Enemy* aux = enemies[i];
				enemies.erase(enemies.begin() + i);
				delete aux;
			}
		}
	}
	//crear enemigos con el el level al que este el levelGame

	if (_levelGame % 5 == 0){
		//toca boss del nivel al que este levelGame
	}
	//Final
	_levelGame++;
}


WaveManager::~WaveManager()
{
}

float WaveManager::timeGame(){

	return _time;
}

int WaveManager::levelPlayer(){

	return _level;
}

int WaveManager::countEnemies(){

	return _enemies;
}

int WaveManager::countBoss(){

	return _boss;
}

int WaveManager::countBullets(){

	return _bullets;
}

int WaveManager::countPots(){

	return _pots;
}

