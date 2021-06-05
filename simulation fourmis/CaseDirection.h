#ifndef __CASEDIRECTION_H__
#define __CASEDIRECTION_H__

#include <cstdint>

enum class CaseDirection : uint32_t
{
	Haut = 0,
	Droite = 1,
	Bas = 2,
	Gauche = 3,
};

#endif