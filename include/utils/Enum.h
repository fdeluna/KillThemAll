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
	OBSTACLE = 1,
	MAP_FLOOR = 2,
	HELL = 4,
	PLAYER = 8,
	ENEMY = 16
};


enum class EnemyState
{
	ATTACK,
	MOVE,
	DIE,
	HITTED

};

static const short player_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMY;
static const short enemy_collides_with = PLAYER | OBSTACLE | MAP_FLOOR | HELL;
static const short obstacle_collides_with = PLAYER | ENEMY | MAP_FLOOR;
static const short map_floor_collides_with = PLAYER | ENEMY | MAP_FLOOR;
static const short hell_collides_with = PLAYER | ENEMY;

static int sceneNodeNumber = 0;

static int getSceneNodeNumber(){
	sceneNodeNumber++;
	return sceneNodeNumber;
}

#endif