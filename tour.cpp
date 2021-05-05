#include "tour.h"
#include "iostream"
using namespace std;

//_______________________________TOUR_________________________________

/**
 * @brief Tour::Tour, constructor of a tower
 * @param parent
 * @param color
 * @param owner
 * @param width
 * @param height
 * @param x
 * @param y
 */
Tour::Tour(QWidget *parent, QString color, Playerjeu * owner,  int width, int height, int x,int y)
{
    this->lbl = new QLabel(parent);
    this->setImage(color);
    this->width = width;
    this->height = height;
    this->color = color;
    this->x = x;
    this->y = y;
    this->lbl->move(x,y);
    this->owner = owner;
    this->lbl->setVisible(true);
}

/**
 * @brief Tour::~Tour, destructor of the piece
 */
Tour::~Tour(){
    delete this->lbl;
}

//_______________________________METHOD_________________________________

/**
 * @brief Tour::setImage, load the image of the piece
 * @param color
 */
void Tour::setImage(QString color){
    if(color==("Blanc")){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/tour_blanc.png")); //Image tour blanche
        this->namePiece = '3';
    }else if(color==("Noir")){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/tour_noir.png"));  //Image tour noire
        this->namePiece = 't';
    }
}

/**
 * @brief Tour::isValidMove, check if the move is possible
 * @param x
 * @param y
 * @param pieces
 * @return
 */
bool Tour::isValidMove(int x, int y,std::vector<Piece*> pieces){
    this->updateAllPossibleMove(pieces);
    if(((x!=this->tabPosX && y==this->tabPosY) || (x==this->tabPosX && y != this->tabPosY)) && this->moveInBoard(x,y) && this->checkIfMate(x,y) && this->IsPossibleMove(x,y,this->allPossibleMove) )
        return true;
    else
        return false;
}

/**
 * @brief Tour::move, movement of a tower
 * @param x
 * @param y
 */
void Tour::move(int x, int y){
    this->lbl->move(x*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),y*TAILLECASE+CHESSBOARD_POS.y());
    this->setTabPosX(x);
    this->setTabPosY(y);
}


/**
 * @brief Tour::updateAllPossibleMove, verify all possible move
 * @param pieces
 */
void Tour::updateAllPossibleMove(std::vector<Piece *> pieces){
    int i=this->tabPosX-1,j=this->tabPosX+1;
    bool alreadyHasEnemy = false;
    while(i>=0){
        if(!this->checkIfMate(i,this->tabPosY) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,i,this->tabPosY) && this->getPieceAt(pieces,i,this->tabPosY)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(i,this->tabPosY));
        }
        i--;
    }

    alreadyHasEnemy = false;
    while(j<8){
        if(!this->checkIfMate(j,this->tabPosY) || alreadyHasEnemy)
        {
            break;
        }
        else{
            if(this->getPieceAt(pieces,j,this->tabPosY) && this->getPieceAt(pieces,j,this->tabPosY)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(j,this->tabPosY));
        }
        j++;
    }

    alreadyHasEnemy = false;
    i=this->tabPosY+1,j=this->tabPosY-1;
    while(i<8){
        if(!this->checkIfMate(this->tabPosX,i) || alreadyHasEnemy)
        {
            break;
        }
        else{
            if(this->getPieceAt(pieces,this->tabPosX,i) && this->getPieceAt(pieces,this->tabPosX,i)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(this->tabPosX,i));
        }
        i++;
    }

    alreadyHasEnemy = false;
    while(j>=0){
        if(!this->checkIfMate(this->tabPosX,j) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,this->tabPosX,j) && this->getPieceAt(pieces,this->tabPosX,j)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(this->tabPosX,j));
        }
        j--;
    }
}

