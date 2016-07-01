#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <Ogre.h>

enum MeshName{
	TILE,
	PLAYERM,
	ENEMYFIGHTERM,
	ENEMYMINE,
	BOSS,
	PLAYERP,
	BULLETP,
	REVOLVER,
	MINE,
	OBSTACLENODE
};

static std::map<MeshName, Ogre::String> MESHES = {
	{ MeshName::TILE, "Tile.mesh" },
	{ MeshName::PLAYERM, "Player.mesh" },
	{ MeshName::ENEMYFIGHTERM, "EnemyFighter.mesh" },
	{ MeshName::ENEMYMINE, "EnemyMine.mesh" },
	{ MeshName::BOSS, "Cylinder.mesh" },
	{ MeshName::PLAYERP, "EnemyFighter.mesh" },
	{ MeshName::BULLETP, "Bullet.mesh" },
	{ MeshName::REVOLVER, "Revolver.mesh" },
	{ MeshName::MINE, "Mina.mesh" },
	{ MeshName::OBSTACLENODE, "Obstacle.mesh" }

};

enum class GameFlowState{

	PLAY,
	GAMEOVER,
	WAVECLEARED
};

enum class EnemyState
{
	ATTACK,
	MOVE,
	DIE
};

enum GameObjectType{
	OBSTACLE = 1,
	MAP_FLOOR = 2,
	HELL = 4,
	PLAYER = 8,
	ENEMYFIGHTER = 16,	
	BULLET = 32,
	MINES = 64,
	MINEENEMY = 128,
	ENEMYMINER = 256
};

static const short player_collides_with = OBSTACLE | MAP_FLOOR | HELL | MINES | ENEMYFIGHTER | MINEENEMY;
static const short enemy_fighter_collides_with = OBSTACLE | MAP_FLOOR | HELL | BULLET | MINES | PLAYER;
static const short enemy_miner_collides_with = OBSTACLE | MAP_FLOOR | HELL | BULLET | MINES;
static const short obstacle_collides_with = PLAYER | ENEMYFIGHTER | ENEMYMINER | MAP_FLOOR | BULLET;
static const short map_floor_collides_with = PLAYER | ENEMYFIGHTER | ENEMYMINER | MAP_FLOOR | BULLET | MINES;
static const short hell_collides_with = PLAYER | ENEMYFIGHTER | ENEMYMINER | BULLET;
static const short bullet_collides_with = OBSTACLE | MAP_FLOOR | HELL | ENEMYFIGHTER | ENEMYMINER;
static const short mines_collides_with = ENEMYFIGHTER | ENEMYMINER | PLAYER | MAP_FLOOR;
static const short enemy_mines_collides_with = PLAYER | MAP_FLOOR;

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
	{ Speed::SLOW, 1.5f },
	{ Speed::NORMAL, 3.0f },
	{ Speed::FAST, 5.0f }

};

enum class SpeedPlayer{
	SLOWP,
	NORMALP,
	FASTP
};

static std::map<SpeedPlayer, float> SPEEDPLAYER = {
	{ SpeedPlayer::SLOWP, 4.0f },
	{ SpeedPlayer::NORMALP, 5.0f },
	{ SpeedPlayer::FASTP, 7.0f }

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
#endif