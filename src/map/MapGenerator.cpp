#include "MapGenerator.h"

void MapGenerator::GenerateMap(){
	_mapSize = Ogre::Vector2(15, 7);
	_mapCenter = Ogre::Vector2((int)_mapSize.x / 2, (int)_mapSize.y / 2);
	

	std::srand(std::time(0));
	int maxNumberObstacules = _mapSize.x * _mapSize.y * 0.5;
	int minNumberObstacules = _mapSize.x * _mapSize.y * 0.3;

	int numberObstacules = rand() % (maxNumberObstacules - minNumberObstacules) + minNumberObstacules;

	std::vector<Node*> gridRow;

	for (int x = 0; x < _mapSize.x; x++){
		for (int y = 0; y < _mapSize.y; y++){
			Ogre::Vector3 position(x, 0, y);
			gridRow.push_back(new Node(_sceneManager, true, position, MESHES[Mesh::TILE]));
		}
		grid.push_back(gridRow);
		gridRow.clear();
	}

	std::vector< std::vector <bool>> obstacleMap;

	initBidimensionalVector(obstacleMap, (int)_mapSize.x, (int)_mapSize.y);
	shuffleArray(grid);

	int currentNumberObstacules = 0;
	std::vector<std::pair<int, int>> randomCoords;

	for (int i = 0; i < numberObstacules;){
		int x = rand() % (int)_mapSize.x;
		int y = rand() % (int)_mapSize.y;

		Ogre::Vector2 coord = grid[x][y]->getNodePosition();
		std::pair<int, int> coordPair(x, y);

		if (!(std::find(randomCoords.begin(), randomCoords.end(), coordPair) != randomCoords.end())){
			randomCoords.push_back(coordPair);
			obstacleMap[(int)coord.x][(int)coord.y] = true;
			currentNumberObstacules++;

			if (_mapCenter != coord && isMapAccessible(obstacleMap, currentNumberObstacules)){				
				float colourPercent = coord.y / (float)_mapSize.y;
				Ogre::Math::lerp<Ogre::ColourValue, float>(Ogre::ColourValue::Black, Ogre::ColourValue::Red, colourPercent);
				grid[x][y]->makeObstacle(Ogre::Vector3(0.5, 10, 0.5), Ogre::Math::lerp<Ogre::ColourValue, float>(Ogre::ColourValue::White, Ogre::ColourValue::Blue, colourPercent));

			}
			else{
				currentNumberObstacules--;
				obstacleMap[coord.x][coord.y] = false;
			}
			i++;
		}
	}


	// TODO REFACTOR TO STYLE SELECTION
	Ogre::Plane plane = createPlane("mapFloor", (int)_mapSize.x, (int)_mapSize.y);
	SceneNodeComponent* planeNode = new SceneNodeComponent(_sceneManager, "PlaneFloor", "mapFloor", Ogre::Vector3::UNIT_SCALE, Ogre::Vector3(_mapCenter.x, 0, _mapCenter.y));
	
	// Render To Texture (MIRROR EFFECT) ------------------------------------
	Ogre::TexturePtr rttM_texture = Ogre::TextureManager::getSingleton().createManual(
		"RttMTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D, 2048, 2048, 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);

	Ogre::RenderTexture *rMtex = rttM_texture->getBuffer()->getRenderTarget();

	Ogre::Camera *camM = _sceneManager->createCamera("MirrorCamera");
	camM->setPosition(_sceneManager->getCamera("PlayState")->getPosition());
	camM->setOrientation(_sceneManager->getCamera("PlayState")->getOrientation());
	camM->setAspectRatio(_sceneManager->getCamera("PlayState")->getAspectRatio());

	rMtex->addViewport(camM);
	rMtex->getViewport(0)->setClearEveryFrame(true);
	rMtex->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	rMtex->getViewport(0)->setOverlaysEnabled(false);
	rMtex->setAutoUpdated(true);

	Ogre::MaterialPtr mMPtr = Ogre::MaterialManager::getSingleton().create(
		"RttMMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Technique* matMTechnique = mMPtr->createTechnique();
	matMTechnique->createPass();
	Ogre::TextureUnitState *t = mMPtr->getTechnique(0)->getPass(0)->createTextureUnitState("tile.png");	
	t->setScrollAnimation(-0.5, 0);
	t = mMPtr->getTechnique(0)->getPass(0)->createTextureUnitState("RttMTex");
	t->setColourOperationEx(Ogre::LBX_BLEND_MANUAL, Ogre::LBS_TEXTURE, Ogre::LBS_CURRENT, Ogre::ColourValue::White, Ogre::ColourValue::White, 0.5);	
	t->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
	t->setProjectiveTexturing(true, camM);
			
	camM->enableReflection(plane);
	camM->enableCustomNearClipPlane(plane);

	planeNode->setMaterialName("RttMMat");		
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

	int totalNoObstacleTiles = (int)((_mapSize.x * _mapSize.y) - currentNumberObstacle);

	bool aux = totalNoObstacleTiles == noObstacletiles;
	return totalNoObstacleTiles == noObstacletiles;
}