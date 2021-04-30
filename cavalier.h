#ifndef CAVALIER_H
#define CAVALIER_H

#include "piece.h"
#include "playerjeu.h"

class Cavalier : public Piece
{
public:

    Cavalier(QWidget *parent, QString color,Playerjeu* owner , int width, int height, int x,int y);
    void setImage(QString color);
    void move(int x, int y);
    bool isValidMove(int x, int y,std::vector<Piece*> pieces);
    void updateAllPossibleMove(std::vector<Piece*> pieces);
    ~Cavalier();
};

#endif // CAVALIER_H
