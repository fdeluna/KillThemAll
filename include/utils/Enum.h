#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <Ogre.h>

enum Mesh{
	TILE
};

static std::map<Mesh, Ogre::String> MESHES = {
	{ TILE, "Tile.mesh"}
};

#endif