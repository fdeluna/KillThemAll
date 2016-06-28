#include "Map.h"

void Map::GenerateMap(){
	_mapSize = Ogre::Vector2(10, 10);
	_mapCenter = Ogre::Vector2(_mapSize.x / 2, _mapSize.y / 2);

	SceneNodeComponent* hell = new SceneNodeComponent(_sceneManager, "Hell", MESHES[MeshName::OBSTACLENODE], Ogre::Vector3(50, 1, 50), Ogre::Vector3(_mapCenter.x - 0.5, -10, _mapCenter.y - 0.5));
	RigidBodyComponent* hellBody = new RigidBodyComponent((GameObject*)this, GameObjectType::HELL, hell);
	hell->setMaterialName("Ground");

	// TODO REFACTOR TO STYLE SELECTION
	Ogre::Plane plane = createPlane("mapFloor", _mapSize.x + 0.2, _mapSize.y + 0.2);
	planeNode = new SceneNodeComponent(_sceneManager, "PlaneFloor", "mapFloor", Ogre::Vector3::UNIT_SCALE, Ogre::Vector3(_mapCenter.x - 0.5, 0, _mapCenter.y - 0.5));

	rigidBodyComponent = new RigidBodyComponent(nullptr, GameObjectType::MAP_FLOOR, planeNode);
	rigidBodyComponent->setWorldPosition(Ogre::Vector3(_mapCenter.x - 0.5, 0, _mapCenter.y - 0.5));
	planeNode->setMaterialName("Floor");

	// MAP GENERATION
	std::vector<MapNode*> gridRow;
	for (int x = 0; x < _mapSize.x; x++){
		for (int y = 0; y < _mapSize.y; y++){
			Ogre::Vector3 position(x, 0, y);
			MapNode* aux = new MapNode(_sceneManager, true, position, MESHES[MeshName::TILE], planeNode->getSceneNode(), x, y);
			gridRow.push_back(aux);
		}
		grid.push_back(gridRow);
		gridRow.clear();
	}


	std::vector< std::vector <bool>> obstacleMap;
	std::vector<std::pair<int, int>> randomCoords;
	std::vector< std::vector <MapNode*>> shuffledgrid = grid;
	std::srand(std::time(0));
	int currentNumberObstacules = 0;

	int maxNumberObstacules = _mapSize.x * _mapSize.y * 0.25;
	int minNumberObstacules = _mapSize.x * _mapSize.y * 0.15;
	int numberObstacules = rand() % (maxNumberObstacules - minNumberObstacules) + minNumberObstacules;

	initBidimensionalVector(obstacleMap, (int)_mapSize.x, (int)_mapSize.y);
	shuffleArray(shuffledgrid);

	for (int i = 0; i < numberObstacules;){
		int x = rand() % (int)_mapSize.x;
		int y = rand() % (int)_mapSize.y;

		Ogre::Vector2 coord = shuffledgrid[x][y]->getNodePosition();
		std::pair<int, int> coordPair(x, y);

		if (!(std::find(randomCoords.begin(), randomCoords.end(), coordPair) != randomCoords.end())){
			randomCoords.push_back(coordPair);
			obstacleMap[(int)coord.x][(int)coord.y] = true;
			currentNumberObstacules++;

			if (_mapCenter != coord && isMapAccessible(obstacleMap, currentNumberObstacules)){
				float colourPercent = coord.y / (float)_mapSize.y;
				Ogre::Math::lerp<Ogre::ColourValue, float>(Ogre::ColourValue::Black, Ogre::ColourValue::Red, colourPercent);
				shuffledgrid[x][y]->makeObstacle(Ogre::Vector3(0.5, 0.75, 0.5), MESHES[MeshName::OBSTACLENODE]);
			}
			else{
				currentNumberObstacules--;
				obstacleMap[coord.x][coord.y] = false;
			}
			i++;
		}
	}
}

void Map::cleanMap(){
	_mapSize = Ogre::Vector2();
	_mapCenter = Ogre::Vector2();
	if (!grid.empty()){
		for (int i = 0; i < grid.size(); i++){
			for (int j = 0; j < grid[i].size(); j++){
				MapNode* aux = grid[i][j];
				if (aux){
					delete aux;
				}
			}
		}
		delete rigidBodyComponent;
		delete planeNode;
	}
	grid.clear();
}

MapNode* Map::nodeFromWorldPosition(Ogre::Vector3 position){

	MapNode* node = nullptr;
	float distanceFromNode = 1;
	position = Ogre::Vector3(position.x, 0, position.z);
	for (int x = 0; x < grid.size(); x++){
		for (int y = 0; y < grid[x].size(); y++){
			if (grid[x][y]->isWakable()){
				Ogre::Vector3 nodePosition(grid[x][y]->getSceneNode()->getSceneNode()->getPosition().x, 0, grid[x][y]->getSceneNode()->getSceneNode()->getPosition().z);
				float distanceAux = position.distance(nodePosition);
				if (distanceAux < distanceFromNode){
					node = grid[x][y];
					distanceFromNode = distanceAux;
				}
			}
		}
	}
	return node;
}

std::vector<MapNode*> Map::getNeighbours(MapNode* node){
	std::vector<MapNode*> neighbours;

	for (int x = -1; x <= 1; x++){
		for (int y = -1; y <= 1; y++){
			if ((x == 0 && y != 0) || (y == 0 && x != 0)){
				int gridX = node->getGridX() + x;
				int gridY = node->getGridY() + y;

				if (gridX >= 0 && gridX < _mapSize.x && gridY >= 0 && gridY < _mapSize.y){
					if (grid[gridX][gridY]->isWakable()){
						neighbours.push_back(grid[gridX][gridY]);
					}
				}
			}
		}
	}
	return neighbours;
}

bool Map::isMapAccessible(std::vector< std::vector <bool>> obstacleMap, int currentNumberObstacle){

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

	int totalNoObstacleTiles = (int)((_mapSize.x * _mapSize.y) - currentNumberObstacle);

	bool aux = totalNoObstacleTiles == noObstacletiles;
	return totalNoObstacleTiles == noObstacletiles;
}


Ogre::Vector3 Map::getRandomNodePosition(){
	Ogre::Vector3 nodePosition = Ogre::Vector3::ZERO;


	while (nodePosition == Ogre::Vector3::ZERO){
		int x = rand() % (int)_mapSize.x;
		int y = rand() % (int)_mapSize.y;

		if (grid[x][y]->isWakable()){
			nodePosition = grid[x][y]->getSceneNode()->getSceneNode()->getPosition();
		}
	}

	return nodePosition;
}