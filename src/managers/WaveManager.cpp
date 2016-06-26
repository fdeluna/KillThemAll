#include "WaveManager.h"

template<> WaveManager* Ogre::Singleton<WaveManager>::msSingleton = 0;

WaveManager* WaveManager::getSingletonPtr() {
	return msSingleton;
}

WaveManager& WaveManager::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}

void WaveManager::initWave(){
	//std::cout << "LEVEL: " << _levelGame << std::endl;
	_map = new Map(_sceneManager);
	_map->GenerateMap();
	_waveEnemies = 10;
	_waveEnemies = _waveEnemies * (_levelGame);
	_waveEnemiesKilled = 0;
	_levelGame++;	
}

void WaveManager::cleanWave(){
	if (_map){
		_map->cleanMap();
	}
	if (_enemies.size() > 0){
		for (int i = 0; i < _enemies.size(); i++){
			Enemy* aux = _enemies[i];
			_enemies.erase(_enemies.begin() + i);
			delete aux;
		}
	}
	_enemies.clear();
}

void WaveManager::wave(float deltaTime)
{
	_spawnEnemy += deltaTime;
	if (_spawnEnemy >= 1 && _enemies.size() <= _waveEnemies){
		_spawnEnemy = 0;
		EnemyFighter* newEnemy = nullptr;
		Ogre::Vector3 enemyPosition = _map->getRandomNodePosition();
		int enemyType = (rand() % 10) + 1;

		if (enemyType > 2) {
			newEnemy = new EnemyFighter(_sceneManager, Ogre::Vector3(enemyPosition.x, 0.5, enemyPosition.z), MESHES[MeshName::ENEMYFIGHTER], _player,_levelGame);

		}
		_enemies.push_back(newEnemy);
	}


	if (_enemies.size() > 0){
		for (int i = 0; i < _enemies.size(); i++){
			if (_enemies[i] && _enemies[i]->isActive()){
				_enemies[i]->update(deltaTime);
			}
			else{
				_waveEnemiesKilled++;
				Enemy* aux = _enemies[i];
				_enemies.erase(_enemies.begin() + i);
				delete aux;
			}
		}
	}
}
