#include <SDL.h>
#include <SDL_mixer.h>
#include "AudioManager.h"

template<> AudioManager* Ogre::Singleton<AudioManager>::msSingleton = 0;


AudioManager::AudioManager(){

	if (!_initSDL()){
		_initSDL();
	}


	_pTrackManager = OGRE_NEW TrackManager;
	_pSoundFXManager = OGRE_NEW SoundFXManager;
	_mainTrack = _pTrackManager->load("AUDIO/area1Music.wav");
	_introTrack = _pTrackManager->load("AUDIO/menuMusic.wav");
	_soundButton = _pSoundFXManager->load("AUDIO/sndAmmoPickup.wav");
	_soundBack = _pSoundFXManager->load("AUDIO/sndEnemySlash.wav");
	_soundPlay = _pSoundFXManager->load("AUDIO/sndLevelUp.wav");

	_soundShoot = _pSoundFXManager->load("AUDIO/sndPistol.wav");

	_soundPotion = _pSoundFXManager->load("AUDIO/sndRoll.wav");
	_soundMine = _pSoundFXManager->load("AUDIO/sndSniperTarget.wav");
	_soundMineExplote = _pSoundFXManager->load("AUDIO/sndGrenade.wav");

	_soundHitPlayer = _pSoundFXManager->load("AUDIO/sndPlayerHit.wav");
	_soundDiePlayer = _pSoundFXManager->load("AUDIO/sndPlayerDeath.wav");

	_soundSpawn = _pSoundFXManager->load("AUDIO/sndSelect.wav");
	_soundUpgrade = _pSoundFXManager->load("AUDIO/sndEnemyDie.wav");

	_soundHitEnemy = _pSoundFXManager->load("AUDIO/sndHit.wav");
	_soundDieEnemy = _pSoundFXManager->load("AUDIO/sndEnemyDie.wav");	
		
	for (int i = 0; i < 32; i++){ Mix_Volume(i, 40); }
}

void AudioManager::playAudio(Audio audio){

	switch (audio)
	{
	case Audio::PLAYSTATE:

		_mainTrack->play();
		Mix_VolumeMusic(40);
		break;
	case Audio::SPAWN:

		_soundSpawn->play();

		break;
	case Audio::HITPLAYER:

		_soundHitPlayer->play();

		break;
	case Audio::KILLPLAYER:

		_soundDiePlayer->play();

		break;
	case Audio::KILLENEMY:

		_soundDieEnemy->play();

		break;
	case Audio::SHOOT:
		_soundShoot->play();

		break;
	case Audio::UPGRADE:
		_soundUpgrade->play();

		break;
	case Audio::HITWALL:
		_soundHitWall->play();

		break;
	case Audio::POTION:
		_soundPotion->play();

		break;

	case Audio::RELOAD:
		_soundReload->play();

		break;
	case Audio::HITENEMY:


		_soundHitEnemy->play();

		break;
	case Audio::PLAY:


		_soundPlay->play();

		break;
	case Audio::ALARM:


		_soundAlarm->play(1);

		break;

	case Audio::NOAMMO:


		_soundNoAmmo->play();

		break;

	case Audio::BUTTON:


		_soundButton->play();

		break;
	case Audio::BACK:


		_soundBack->play();

		break;
	case Audio::MINE:


		_soundMine->play();

		break;
	case Audio::MINEEXPLOSION:


		_soundMineExplote->play();

		break;
	case Audio::INTROSTATE:

		_introTrack->play();
		Mix_VolumeMusic(40);
		break;
	default:
		break;
	}
}


AudioManager* AudioManager::getSingletonPtr()
{
	return msSingleton;
}

AudioManager& AudioManager::getSingleton()
{
	assert(msSingleton);
	return *msSingleton;
}


bool AudioManager::_initSDL() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		return false;
	}	

	atexit(SDL_Quit);
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
		return false;
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);	
	atexit(Mix_CloseAudio);

	return true;
}
