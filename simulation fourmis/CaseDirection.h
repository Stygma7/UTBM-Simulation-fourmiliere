#ifndef __CASEDIRECTION_H__
#define __CASEDIRECTION_H__

#include <cstdint>

// définit la direction haut, gauche, bas et droite d'une direction de 360°
enum class CaseDirection : uint32_t
{
	Haut = 0,
	Droite = 1,
	Bas = 2,
	Gauche = 3,
};

#endif