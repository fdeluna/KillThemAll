/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
 *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *********************************************************************/
#define UNUSED_VARIABLE(x) (void)x

#include "GameManager.h"
#include "PlayState.h"
#include "IntroState.h"
#include "WaveCompleteState.h"
#include "GameOverState.h"
#include <iostream>

using namespace std;

int main() {

	//-------
	GameManager* game = new GameManager();
	PlayState* playState = new PlayState();
	IntroState* introState = new IntroState();
	WaveCompleteState* waveCompleteState = new WaveCompleteState();
	GameOverState* gameOverState = new GameOverState();	
	try
	{
		// Inicializa el juego y transición al primer estado.
		game->start(IntroState::getSingletonPtr());
	}
	catch (Ogre::Exception& e)
	{
		std::cerr << "Excepción detectada: " << e.getFullDescription();
	}

	delete game;

	return 0;
}