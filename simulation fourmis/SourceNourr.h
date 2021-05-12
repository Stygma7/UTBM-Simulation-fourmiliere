#pragma once

class SourceNourr
{
private:
    int qteNourr = 5;

public:
    SourceNourr();
    int getquantite() { return qteNourr; }
    void pickNourr();
};