#ifndef AudioController_H
#define AudioController_H

#include <Ogre.h>

#include "Enum.h"
#include "TrackManager.h"
#include "SoundFXManager.h"
#include <SDL_mixer.h>

class AudioController : public Ogre::Singleton<AudioController>{

public:
	AudioController();
	~AudioController();

	void playAudio(Audio audio);

	static AudioController& getSingleton();
	static AudioController* getSingletonPtr();

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