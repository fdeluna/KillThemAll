#include "PathFinder.h"

std::vector<Node*> PathFinder::FindPath(Ogre::Vector3 origin, Ogre::Vector3 destiny){

	Node* startNode = _currentMap->nodeFromWorldPosition(origin);
	Node* targetNode = _currentMap->nodeFromWorldPosition(destiny);

	std::vector<Node*> openSet;
	std::vector<Node*> closeSet;
	std::vector<Node*> path;

	std::list<Node*> list;

	openSet.push_back(startNode);

	while (openSet.size() > 0){
		Node* currentNode = openSet[0];		
		/*for (int i = 0; i < openSet.size(); i++){
			if (openSet[i]->getTotalCost() < currentNode->getTotalCost() || openSet[i]->getTotalCost() == currentNode->getTotalCost() && openSet[i]->getDcost() < currentNode->getDcost()){
				currentNode = openSet[i];
			}
		}*/

		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());		
		closeSet.push_back(currentNode);

		
		if (currentNode == targetNode){			
			Node* endNode = targetNode;
			while (endNode != startNode){
				path.push_back(endNode);
				endNode->getSceneNode()->setDiffuseColor(Ogre::ColourValue::White);				
				endNode = endNode->getParent();
			}
			std::reverse(path.begin(), path.end());			
			return path;
		}
		
		for (Node* neighbour : _currentMap->getNeighbours(currentNode)){			
			if (neighbour->isWakable() && std::find(closeSet.begin(), closeSet.end(), neighbour) == closeSet.end()){

				int movementCostToNeighbour = currentNode->getSCost() + getDistance(currentNode, neighbour);

				if (movementCostToNeighbour < neighbour->getSCost() || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()){
					neighbour->setScost(movementCostToNeighbour);
					neighbour->setDcost(getDistance(neighbour, targetNode));					
					neighbour->setParent(currentNode);

					if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()){						
						openSet.push_back(neighbour);
						std::sort(openSet.begin(), openSet.end(), nodeGreaterThan);
					}
				}
			}
		}
	}
}





int PathFinder::getDistance(Node* nodeA, Node* nodeB){

	int distance = 0;

	int distanceX = Ogre::Math::Abs(nodeA->getGridX() - nodeB->getGridX());
	int distanceY = Ogre::Math::Abs(nodeA->getGridY() - nodeB->getGridY());

	if (distanceX > distanceY){
		distance = 14 * distanceY + 10 * (distanceX - distanceY);
	}
	else{
		distance = 14 * distanceX + 10 * (distanceY - distanceX);
	}

	return distance;
}
