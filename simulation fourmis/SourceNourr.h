#ifndef __SOURCENOURR_H__
#define __SOURCENOURR_H__

class SourceNourr
{
private:
    int qteNourr;

public:
    SourceNourr();

    int getquantite() { return qteNourr; }
    // réduit la quantité de nourriture
    int pickNourr(int);
};

#endif