#ifndef PION_H
#define PION_H

#include "piece.h"
#include "constante.h"
#include "QPoint"
#include "chessboard.h"

class Pion : public Piece
{
public:
    Pion(QWidget *parent, QString color, Playerjeu* owner, int width, int height, int x,int y);
    void setImage(QString color);
    void move(int x, int y);
    bool isValidMove(int x, int y,std::vector<Piece *> pieces);
    void firstMovePlayed();
    bool canAttack(char chessboard[8][8]);
    void test(std::vector<Piece *> pieces);
    ~Pion();
    void updateAllPossibleMove(std::vector<Piece*> pieces);
   // bool IsPossibleMove(int x, int y, std::vector<QPoint> possibleMove);

private:
    bool firstMove = true;

signals:
    void maxAtteint();

};

#endif // PION_H
