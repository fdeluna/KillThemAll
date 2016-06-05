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
	SoundFXPtr _soundShoot;
	SoundFXPtr _soundReload;
	SoundFXPtr _soundShootHitMonster;
	SoundFXPtr _soundSpawn;
	SoundFXPtr _soundAlarm;
	SoundFXPtr _soundNoAmmo;




};
#endif