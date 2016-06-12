#include "WaveManager.h"

template<> WaveManager* Ogre::Singleton<WaveManager>::msSingleton = 0;

WaveManager::WaveManager()
{
}

void WaveManager::wave()
{
	//crear enemigos con el el level al que este el levelGame

	if (levelGame%5 == 0){
		//toca boss del nivel al que este levelGame
	}
	//Final
	levelGame++;
}


WaveManager::~WaveManager()
{
}

float WaveManager::timeGame(){

	return time;
}

int WaveManager::levelPlayer(){

	return level;
}

int WaveManager::countEnemies(){

	return enemies;
}

int WaveManager::countBoss(){

	return boss;
}

int WaveManager::countBullets(){

	return bullets;
}

int WaveManager::countPots(){

	return pots;
}


WaveManager*
WaveManager::getSingletonPtr()
{
	return msSingleton;
}

WaveManager&
WaveManager::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}