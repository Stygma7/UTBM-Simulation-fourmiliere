#ifndef __CASETYPE_H__
#define __CASETYPE_H__

#include <cstdint>

// renseigne sur le type d'une case
enum class Type : uint32_t
{
	Normal = 0,
	Obstacle = 1,
	SrcNourr = 2,
};

#endif