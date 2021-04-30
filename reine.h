#ifndef REINE_H
#define REINE_H

 #include "piece.h"
#include <QPoint>
class Reine : public Piece
{
public:
    Reine(QWidget *parent, QString color,Playerjeu * owner , int width, int height, int x,int y);
    void setImage(QString color);
    void move(int x, int y);
    bool isValidMove(int x, int y,std::vector<Piece*> pieces);
    ~Reine();
    void updateAllPossibleMove(std::vector<Piece*> pieces);
   // bool IsPossibleMove(int x, int y, std::vector<QPoint> possibleMove);
};

#endif // REINE_H
