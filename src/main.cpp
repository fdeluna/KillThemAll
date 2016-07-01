#define UNUSED_VARIABLE(x) (void)x

#include "GameManager.h"
#include "PlayState.h"
#include "IntroState.h"
#include "WaveCompleteState.h"
#include "GameOverState.h"
#include <iostream>

using namespace std;

int main() {


	GameManager* game = new GameManager();
	PlayState* playState = new PlayState();
	IntroState* introState = new IntroState();
	WaveCompleteState* waveCompleteState = new WaveCompleteState();
	GameOverState* gameOverState = new GameOverState();	
	try
	{		
		game->start(IntroState::getSingletonPtr());
	}
	catch (Ogre::Exception& e)
	{
		std::cerr << "Excepción detectada: " << e.getFullDescription();
	}

	delete game;

	return 0;
}