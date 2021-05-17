#pragma once

class SourceNourr
{
private:
    int qteNourr;

public:
    SourceNourr();

    int getquantite() { return qteNourr; }
    // réduit la quantité de nourriture
    void pickNourr();
};