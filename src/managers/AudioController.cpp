#include <SDL.h>
#include <SDL_mixer.h>
#include "AudioController.h"

template<> AudioController* Ogre::Singleton<AudioController>::msSingleton = 0;


AudioController::AudioController(){

	_initSDL();

	_pTrackManager = OGRE_NEW TrackManager;
	_pSoundFXManager = OGRE_NEW SoundFXManager;
	_mainTrack = _pTrackManager->load("219147_zagi2_retro-crime-movie-loop-2_converted.wav");
	_soundShoot = _pSoundFXManager->load("shoot4.wav");
	_soundShootHitMonster = _pSoundFXManager->load("hitMonster.wav");
	_soundReload = _pSoundFXManager->load("reload.wav");
	_soundSpawn = _pSoundFXManager->load("spawn2.wav");
	_soundAlarm = _pSoundFXManager->load("alarm.wav");
	_soundNoAmmo = _pSoundFXManager->load("noAmmo.wav");
	for (int i = 0; i < 32; i++){ Mix_Volume(i, 20); }
	


}

void AudioController::playAudio(Audio audio){

	
	switch (audio)
	{
	case Audio::PLAYSTATE:

		_mainTrack->play();
		Mix_VolumeMusic(40);
		break;
	case Audio::SHOOT:
		_soundShoot->play();
		
		break;
	case Audio::SPAWN:
	
		_soundSpawn->play();

		break;
	case Audio::RELOAD:
		_soundReload->play();

		break;
	case Audio::HITENEMY:

		
		_soundShootHitMonster->play();

		break;
	case Audio::ALARM:


		_soundAlarm->play(1);

		break;
	case Audio::NOAMMO:


		_soundNoAmmo->play();

		break;

		
	default:
		break;
	}
}


AudioController* AudioController::getSingletonPtr()
{
	return msSingleton;
}

AudioController& AudioController::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}


bool AudioController::_initSDL() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		return false;
	}
	//// Llamar a  SDL_Quit al terminar.

	atexit(SDL_Quit);

	//// Inicializando SDL mixer...
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
		return false;
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	//// Llamar a Mix_CloseAudio al terminar.
	atexit(Mix_CloseAudio);

	return true;	
}
