#ifndef PIECE_H
#define PIECE_H
#include <QMouseEvent>
#include <QLabel>
#include "constante.h"

class Playerjeu;

class Piece
{
public:
    int getX();
    int getY();
    Playerjeu * getOwner();
    void setX(int x);
    void setY(int y);
    int getWidth();
    int getHeigth();
    int getOldX();
    int getOldY();
    void setOldX(int x);
    void setOldY(int y);
    int getTabPosX();
    int getTabPosY();
    void setTabPosX(int x);
    void setTabPosY(int y);
    virtual void move(int x, int y);
    virtual bool isValidMove(int x, int y, std::vector<Piece *> pieces);
    virtual  void setImage(QString color);
    char getPieceName();
    void centrer(int x, int y);
    QString getColor();
    std::vector<QPoint> allPossibleMove;
    bool getIsPion();
    bool getIsKing();
    void destructPiece(int x, int y);
    virtual ~Piece();
    virtual void updateAllPossibleMove(std::vector<Piece *> pieces);
    void setVerticalBlocked(bool state);
    void setHorizontalBlocked(bool state);
    Piece *getPieceAt(std::vector<Piece*> pieces, int x, int y);
    bool checkIfMate(int x, int y);
    bool IsPossibleMove(int x, int y, std::vector<QPoint> possibleMove);
    QPoint& operator -(const QPoint& p);
    QPoint pos;

protected:
    bool moveInBoard(int x, int y);
    QLabel  *lbl;    //Image de la pièce
    QString color;  //Couleur de la pièce
    char namePiece;
    int width;  //Largeur de la pièce
    int height; //Hauteur de la pièce
    int x;  //Position x de la pièce
    int y;  //Position y de la pièce
    int oldX;
    int oldY;
    int tabPosX;    //position ligne de la pièce dans le tableau
    int tabPosY;    //position colonne de la pièce dans le tableau
    Playerjeu* owner;
    bool isPion = false;
    bool isKing = false;

    /*
    bool verticalBlocked=false;
    bool horizontalBlocked=false;*/

};

#endif // PIECE_H
