#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <Ogre.h>

enum Mesh1{
	TILE,
	PLAYERM,
	ENEMYFIGHTER,
	BOSS,
	PLAYERP
};

static std::map<Mesh1, Ogre::String> MESHES = {
	{ Mesh1::TILE, "Tile.mesh" },
	{ Mesh1::PLAYERM, "Cube.001.mesh" },
	{ Mesh1::ENEMYFIGHTER, "Robot.mesh" },
	{ Mesh1::BOSS, "Cylinder.mesh"},
	{ Mesh1::PLAYERP, "glavni_lik.mesh" }
};


enum GameObjectType{
	OBSTACLE,
	MAP_FLOOR,
	HELL,
	PLAYER,
	BULLETR
};


static int sceneNodeNumber = 0;

static int getSceneNodeNumber(){
	sceneNodeNumber++;
	return sceneNodeNumber;
}
enum class Audio
{
	INTROSTATE,
	PLAYSTATE,
	BUTTON,
	SHOOT,
	HITENEMY,
	HITCORE,
	GAMEOVER,
	WIN,
	RELOAD,
	SPAWN,
	ALARM,
	NOAMMO,
	KILLENEMY

};

enum class Speed{

	SLOW,
	NORMAL,
	FAST

};

static std::map<Speed, float> SPEEDS = {
	{ Speed::SLOW, 1.5f },
	{ Speed::NORMAL, 2.0f },
	{ Speed::FAST, 2.5f }

};


enum class AttackVelocity{

	SLOW,
	NORMAL,
	FAST

};

static std::map<AttackVelocity, float> ATTACKVELOCITIES = {
	{ AttackVelocity::SLOW, 1.5f },
	{ AttackVelocity::NORMAL, 2.0f },
	{ AttackVelocity::FAST, 2.5f }

};

enum class EnemyState
{
	ATTACK,
	MOVE,
	DIE,
	HITTED

};

enum class ScopeWeapon{

	LONG,
	MELEE,
	SHORT
};

enum class CadenceWeapon{

	SLOW,
	NORMAL,
	FAST
};

static std::map<CadenceWeapon, float>	CADENCE = {
	{ CadenceWeapon::SLOW, 1.5f },
	{ CadenceWeapon::NORMAL, 2.0f },
	{ CadenceWeapon::FAST, 2.5f }

};

#endif