#ifndef FOU_H
#define FOU_H

#include "piece.h"

class Fou : public Piece
{
public:
    Fou(QWidget *parent, QString color,Playerjeu * owner , int width, int height, int x,int y);
    void setImage(QString color);
    void move(int x, int y);
    bool isValidMove(int x, int y,std::vector<Piece*> pieces);
    ~Fou();
    void updateAllPossibleMove(std::vector<Piece*> pieces);
    //bool IsPossibleMove(int x, int y, std::vector<QPoint> possibleMove);
};

#endif // FOU_H
