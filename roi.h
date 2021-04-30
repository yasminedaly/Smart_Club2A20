#ifndef ROI_H
#define ROI_H

#include "piece.h"
#include <QMouseEvent>
#include <QDebug>
#include "case.h"

class Roi : public Piece
{
public:
    Roi(QWidget *parent, QString color,Playerjeu * owner, int width, int height, int x,int y);
    void move(int x, int y);
    bool isValidMove(int x, int y,std::vector<Piece*> pieces);
    void setImage(QString color);
    void updateAllPossibleMove(std::vector<Piece*> pieces);
    ~Roi();
};

#endif // ROI_H
