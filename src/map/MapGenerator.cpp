#include "MapGenerator.h"



void MapGenerator::GenerateMap(){
	_mapSize = Ogre::Vector2(15, 7);

	std::srand(std::time(0));
	int maxNumberObstacules = _mapSize.x * _mapSize.y * 0.55;
	int minNumberObstacules = _mapSize.x * _mapSize.y * 0.3;
	int numberObstacules = rand() % (maxNumberObstacules - minNumberObstacules) + minNumberObstacules;
	std::cout << "Obstacles:" << numberObstacules << std::endl;

	std::vector<Node*> gridRow;

	for (int x = 0; x < _mapSize.x; x++){
		for (int y = 0; y < _mapSize.y; y++){						
			Ogre::Vector3 position(-_mapSize.x / 2 + x, 0, -_mapSize.y / 2 + y);
			//Node* node = new Node(_sceneManager,true, position, MESHES[Mesh::TILE]);
			//grid.push_back(node);		
			gridRow.push_back(new Node(_sceneManager, true, position, MESHES[Mesh::TILE]));
		}
		grid.push_back(gridRow);
		gridRow.clear();
	}

	for (int i = 0; i < numberObstacules;){
		int x = rand() % (int)_mapSize.x;
		int y = rand() % (int)_mapSize.y;
		
		if (grid[x][y]->isWakable()){
			grid[x][y]->setScale(Ogre::Vector3(0.5, 5, 0.5));
			grid[x][y]->setWalkable(false);
			i++;
		}

	}
}

