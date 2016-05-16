#include "MapGenerator.h"



void MapGenerator::GenerateMap(){
	_mapSize = Ogre::Vector2(10, 10);
	_mapCenter = Ogre::Vector2((int)_mapSize.x / 2, (int)_mapSize.y / 2);

	std::srand(std::time(0));
	int maxNumberObstacules = _mapSize.x * _mapSize.y * 0.65;
	int minNumberObstacules = _mapSize.x * _mapSize.y * 0.3;

	//int numberObstacules = rand() % (maxNumberObstacules - minNumberObstacules) + minNumberObstacules;
	int numberObstacules = _mapSize.x * _mapSize.y * 0.6;


	std::vector<Node*> gridRow;

	for (int x = 0; x < _mapSize.x; x++){
		for (int y = 0; y < _mapSize.y; y++){
			Ogre::Vector3 position(-_mapSize.x / 2 + x, 0, -_mapSize.y / 2 + y);
			gridRow.push_back(new Node(_sceneManager, true, position, MESHES[Mesh::TILE]));
		}
		grid.push_back(gridRow);
		gridRow.clear();
	}

	std::vector< std::vector <bool>> obstacleMap;

	initBidimensionalVector(obstacleMap, (int)_mapSize.x, (int)_mapSize.y);
	shuffleArray(grid);
	std::cout << "OBSTACLE NUMBER:" << numberObstacules << std::endl;
	int currentNumberObstacules = 0;
	for (int i = 0; i < numberObstacules;){
		//std::cout << "INDEX:" << i << std::endl;
		int x = rand() % (int)_mapSize.x;
		int y = rand() % (int)_mapSize.y;
		/*std::cout << "RAND X:" << x << std::endl;
		std::cout << "RAND Y:" << y << std::endl;*/
		obstacleMap[x][y] = true;
		currentNumberObstacules++;
		//&& isMapAccessible(obstacleMap, currentNumberObstacules
		if (_mapCenter != Ogre::Vector2(x, y)){
			grid[x][y]->setScale(Ogre::Vector3(0.5, 5, 0.5));
			grid[x][y]->setWalkable(false);						
			i++;
		}
		else{
			currentNumberObstacules--;
			obstacleMap[x][y] = false;
		}
	}
	std::cout << "CURRENT OBSTACLE NUMBER:" << currentNumberObstacules << std::endl;
}

bool MapGenerator::isMapAccessible(std::vector< std::vector <bool>> obstacleMap, int currentNumberObstacle){

	std::vector< std::vector <bool>> visitedNodes;
	initBidimensionalVector(visitedNodes, (int)_mapSize.x, (int)_mapSize.y);
	std::queue<Ogre::Vector2> queue;
	queue.push(_mapCenter);

	visitedNodes[(int)_mapCenter.x][(int)_mapCenter.y] = true;

	int noObstacletiles = 1;

	while (queue.size() > 0){
		Ogre::Vector2 tile = queue.front();
		queue.pop();

		for (int x = -1; x <= 1; x++){
			for (int y = -1; y <= 1; y++){
				int neighbourX = tile.x + x;
				int neighbourY = tile.y + y;
				if (x == 0 || y == 0){
					if (neighbourX >= 0 && neighbourX < (int)_mapSize.x && neighbourY >= 0 && neighbourY < (int)_mapSize.y){
						if (!visitedNodes[neighbourX][neighbourY] && !obstacleMap[neighbourX][neighbourY]){
							visitedNodes[neighbourX][neighbourY] = true;
							queue.push(Ogre::Vector2(neighbourX, neighbourY));
							noObstacletiles++;
						}
					}
				}
			}
		}
	}

	int totalNoObstacleTiles = (int)_mapSize.x * _mapSize.y - currentNumberObstacle;

	bool aux = totalNoObstacleTiles == noObstacletiles;
	/*std::cout << "TOTAL OBSTACLE NUMBER:" << totalNoObstacleTiles << std::endl;
	std::cout << "TOTAL NO OBSTACLE TILE:" << noObstacletiles << std::endl;
	std::cout << "MAP IS ACCESSIBLE:" << aux << std::endl;*/
	return totalNoObstacleTiles == noObstacletiles;
}