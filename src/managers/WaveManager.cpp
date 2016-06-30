#include "WaveManager.h"

template<> WaveManager* Ogre::Singleton<WaveManager>::msSingleton = 0;

void WaveManager::resetWaveManager(){
	_bullets = 0;
	_maxEnemiesInMap = 20;
	_waveEnemies = 5;
	_waveEnemiesKilled = 0;
	_enemiesKilled = 0;
	_pots = 0;
	levelGun = 1;
	levelMines = 1;
	levelPots = 1;
	//LevelGame
	_levelGame = 0;
	_numWaves = 1;
	//Game stats
	gameTime = 0;
	minesUsed = 0;
	bulletsUsed = 0;
	potsUsed = 0;
}


void WaveManager::initWave(){
	_map = new Map(_sceneManager);
	_map->GenerateMap();
	_waveEnemies = 10;
	_waveEnemies = _waveEnemies * (_levelGame + 1);
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
	if (_player){
		_playerCurrentLife = _player->getLife();
	}
	_enemies.clear();
}

void WaveManager::wave(float deltaTime)
{
	_spawnEnemy += deltaTime;
	if (_spawnEnemy >= 1.25 && _enemies.size() < _waveEnemies){
		_spawnEnemy = 0;		
		int randomType = rand() % 10 +1;
		Enemy* newEnemy = nullptr;
		Ogre::Vector3 enemyPosition = _map->getRandomNodePosition();

		if (randomType >2){
			newEnemy = new EnemyFighter(_sceneManager, Ogre::Vector3(enemyPosition.x, 0.2, enemyPosition.z), MESHES[MeshName::ENEMYFIGHTERM], _player, _levelGame, GameObjectType::ENEMYFIGHTER);
		}
		else{
			newEnemy = new EnemyMiner(_sceneManager, Ogre::Vector3(enemyPosition.x, 0.2, enemyPosition.z), MESHES[MeshName::ENEMYMINE], _map, _levelGame, GameObjectType::ENEMYMINER);
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


void WaveManager::setPlayer(Player* player){
	_player = player;
	if (_playerCurrentLife != 0){
		_player->setLife(_playerCurrentLife);
	}
};


WaveManager* WaveManager::getSingletonPtr() {
	return msSingleton;
}

WaveManager& WaveManager::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}

