class Position
{
private:
    int x;
    int y;

public:
    int getX() {return x;};
    int getY() {return y;};
    
    void setX(int x) {this->x = x;};
    void setY(int y) {this->y = y;};
    void setPos(int x, int y) {this->x = x; this->y = y;}
    void setPos(Position pos) {this->x = pos.getX(); this->y = pos.getY();}
    bool operator==(Position);
};

