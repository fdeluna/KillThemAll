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
	REVOLVER,
	MINE
};

static std::map<MeshName, Ogre::String> MESHES = {
	{ MeshName::TILE, "Tile.mesh" },
	{ MeshName::PLAYERM, "Player.mesh" },
	{ MeshName::ENEMYFIGHTER, "EnemyFighter.mesh" },
	{ MeshName::BOSS, "Cylinder.mesh" },
	{ MeshName::PLAYERP, "EnemyFighter.mesh" },
	{ MeshName::BULLETP, "Bullet.mesh" },
	{ MeshName::REVOLVER, "Revolver.mesh" },
	{ MeshName::MINE, "Mina.mesh" }

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
	BULLET = 32,
	MINES = 64
};

static const short player_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMY | MINES;
static const short enemy_collides_with = PLAYER | OBSTACLE | MAP_FLOOR | HELL | BULLET |MINES;
static const short obstacle_collides_with = PLAYER | ENEMY | MAP_FLOOR | BULLET;
static const short map_floor_collides_with = PLAYER | ENEMY | MAP_FLOOR | BULLET | MINES;
static const short hell_collides_with = PLAYER | ENEMY | BULLET;
static const short bullet_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMY;
static const short mines_collides_with = ENEMY | PLAYER | MAP_FLOOR;

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
	KILLENEMY,
	BACK,
	MINE,
	MINEEXPLOSION,
	HITWALL,
	POTION,
	KILLPLAYER,
	PLAY,
	HITPLAYER,
	UPGRADE

};

enum class Speed{

	SLOW,
	NORMAL,
	FAST

};

static std::map<Speed, float> SPEEDS = {
	{ Speed::SLOW, 5.5f },
	{ Speed::NORMAL, 6.5f },
	{ Speed::FAST, 8.5f }

};

enum class SpeedPlayer{

	SLOWP,
	NORMALP,
	FASTP

};

static std::map<SpeedPlayer, float> SPEEDPLAYER = {
	{ SpeedPlayer::SLOWP, 5.0f },
	{ SpeedPlayer::NORMALP, 6.0f },
	{ SpeedPlayer::FASTP, 8.0f }

};

enum class AttackVelocity{

	SLOW,
	NORMAL,
	FAST

};

static std::map<AttackVelocity, float> ATTACKVELOCITIES = {
	{ AttackVelocity::SLOW, 0.5f },
	{ AttackVelocity::NORMAL, 0.3f },
	{ AttackVelocity::FAST, 0.1f }

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