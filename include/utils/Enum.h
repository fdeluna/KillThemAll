#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <Ogre.h>

enum MeshName{
	TILE,
	PLAYERM,
	ENEMYFIGHTER,
	BOSS,
	PLAYERP,
	BULLETP,
	REVOLVER
};

static std::map<MeshName, Ogre::String> MESHES = {
	{ MeshName::TILE, "Tile.mesh" },
	{ MeshName::PLAYERM, "Player.mesh" },
	{ MeshName::ENEMYFIGHTER, "EnemyFighter.mesh" },
	{ MeshName::BOSS, "Cylinder.mesh" },
	{ MeshName::PLAYERP, "EnemyFighter.mesh" },
	{ MeshName::BULLETP, "Bullet.mesh" },
	{ MeshName::REVOLVER, "Revolver.mesh" }
};


enum class EnemyState
{
	ATTACK,
	MOVE,
	DIE,
	HITTED

};

enum GameObjectType{
	OBSTACLE = 1,
	MAP_FLOOR = 2,
	HELL = 4,
	PLAYER = 8,
	ENEMY = 16,
	BULLET = 32
};

static const short player_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMY;
static const short enemy_collides_with = PLAYER | OBSTACLE | MAP_FLOOR | HELL | BULLET;
static const short obstacle_collides_with = PLAYER | ENEMY | MAP_FLOOR | BULLET;
static const short map_floor_collides_with = PLAYER | ENEMY | MAP_FLOOR | BULLET;
static const short hell_collides_with = PLAYER | ENEMY | BULLET;
static const short bullet_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMY;


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