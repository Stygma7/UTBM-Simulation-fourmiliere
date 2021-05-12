#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
    int x = 0;
    int y = 0;

public:
    Position() {}
    Position(int x, int y) {this->x = x; this->y = y;}

    bool operator==(Position);

    int getX() {return x;};
    int getY() {return y;};
    
    void setX(int x) {this->x = x;};
    void setY(int y) {this->y = y;};
    void setPos(int x, int y) {this->x = x; this->y = y;}
    void setPos(Position pos) {this->x = pos.getX(); this->y = pos.getY();}
};

#endif 