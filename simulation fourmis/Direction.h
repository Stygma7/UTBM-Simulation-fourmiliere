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
    // CaseDirection getCaseDir90();
    // CaseDirection getCaseDirm90();
    CaseDirection getCaseDir180();

    void add180();

    void update();
};
