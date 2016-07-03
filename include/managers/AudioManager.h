#ifndef AudioManager_H
#define AudioManager_H

#include <Ogre.h>

#include "Enum.h"
#include "TrackManager.h"
#include "SoundFXManager.h"
#include <SDL_mixer.h>

class AudioManager : public Ogre::Singleton<AudioManager>{

public:
	AudioManager();
	~AudioManager();

	void playAudio(Audio audio);

	static AudioManager& getSingleton();
	static AudioManager* getSingletonPtr();

private:

	bool _initSDL();
	TrackManager* _pTrackManager;
	SoundFXManager* _pSoundFXManager;

	TrackPtr _mainTrack;
	TrackPtr _introTrack;

	SoundFXPtr _soundShoot;
	SoundFXPtr _soundMineExplote;
	SoundFXPtr _soundMine;
	SoundFXPtr _soundPotion;

	SoundFXPtr _soundButton;
	SoundFXPtr _soundUpgrade;
	SoundFXPtr _soundPlay;
	SoundFXPtr _soundBack;

	SoundFXPtr _soundDiePlayer;
	SoundFXPtr _soundDieEnemy;
	SoundFXPtr _soundDieBoss;
	SoundFXPtr _soundSpawn;

	SoundFXPtr _soundHitPlayer;
	SoundFXPtr _soundHitEnemy;
	SoundFXPtr _soundHitWall;


	SoundFXPtr _soundReload;
	SoundFXPtr _soundShootHitMonster;
	SoundFXPtr _soundAlarm;
	SoundFXPtr _soundNoAmmo;

};
#endif