#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <Ogre.h>

enum Mesh{
	TILE,
	PLAYERM
};

static std::map<Mesh, Ogre::String> MESHES = {
	{ Mesh::TILE, "Tile.mesh" },
	{ Mesh::PLAYERM, "Cube.001.mesh" }
};

enum GameObjectType{
	OBSTACLE,
	MAP_FLOOR,
	HELL,
	PLAYER
};

static int sceneNodeNumber = 0;

static int getSceneNodeNumber(){
	sceneNodeNumber++;
	return sceneNodeNumber;
}

#endif