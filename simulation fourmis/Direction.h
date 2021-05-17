#pragma once
#include "CaseDirection.h"

class Direction
{
private:
    int angle;
    CaseDirection caseDir;

    void updateCaseDir();

public:
    Direction();

    int getAngle() { return angle; }
    CaseDirection getCaseDir() { return caseDir; }

    void update();
};
