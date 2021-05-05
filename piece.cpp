#include "piece.h"
#include "iostream"
#include "playerjeu.h"
using namespace std;

//_______________________________PIECE_________________________________
Piece::~Piece(){}

//_______________________________METHOD_________________________________

/**
 * @brief Piece::getWidth
 * @return int
 */
int Piece::getWidth(){
    return this->width;
}

/**
 * @brief Piece::getHeigth
 * @return int
 */
int Piece::getHeigth(){
   return this->height;
}

/**
 * @brief Piece::getY
 * @return int
 */
int Piece::getY(){
    return this->lbl->y();
}

/**
 * @brief Piece::getOwner
 * @return owner
 */
Playerjeu* Piece::getOwner(){
    return this->owner;
}

/**
 * @brief Piece::setOldX
 * @param x
 */
void Piece::setOldX(int x){
    this->oldX =x;
}

/**
 * @brief Piece::setOldY
 * @param y
 */
void Piece::setOldY(int y){
    this->oldY =y;
}

/**
 * @brief Piece::getOldX
 * @return oldX
 */
int Piece::getOldX(){
    return this->oldX;
}

/**
 * @brief Piece::getOldY
 * @return oldY
 */
int Piece::getOldY(){
    return this->oldY;
}

/**
 * @brief Piece::getTabPosX
 * @return tabPosX
 */
int Piece::getTabPosX(){
    return this->tabPosX;
}

/**
 * @brief Piece::getTabPosY
 * @return tabPosYs
 */
int Piece::getTabPosY(){
    return this->tabPosY;
}

/**
 * @brief Piece::setTabPosX
 * @param x
 */
void Piece::setTabPosX(int x){
    this->tabPosX = x;
}

/**
 * @brief Piece::setTabPosY
 * @param y
 */
void Piece::setTabPosY(int y){
    this->tabPosY = y;
}

/**
 * @brief Piece::setX
 * @param x
 */
void Piece::setX(int x){
    this->x = x;
}

/**
 * @brief Piece::setY
 * @param y
 */
void Piece::setY(int y){
    this->y = y;
}

/**
 * @brief Piece::move
 * @param x
 * @param y
 */
void Piece::move(int x,int y){
    this->lbl->move(x*TAILLECASE+CENTRER_PIECE,y*TAILLECASE);
}

/**
 * @brief Piece::isValidMove
 * @param x
 * @param y
 * @param pieces
 * @return bool
 */
bool Piece::isValidMove(int x, int y, std::vector<Piece *> pieces){
    return false;
}

/**
 * @brief Piece::centrer, pour centrer la piece
 * @param x
 * @param y
 */
void Piece::centrer(int x, int y){
    this->lbl->move(x,y);
}

/**
 * @brief Piece::getPieceName
 * @return namePiece
 */
char Piece::getPieceName(){
    return this->namePiece;
}

/**
 * @brief Piece::moveInBoard
 * @param x
 * @param y
 * @return bool
 */
bool Piece::moveInBoard(int x, int y){
    if(x<=7 && x>=0 && y<=7 && y>=0)
        return true;
    else
        return false;
}

/**
 * @brief Piece::getColor
 * @return color
 */
QString Piece::getColor(){
    return this->color;
}

/**
 * @brief Piece::getIsPion
 * @return isPion
 */
bool Piece::getIsPion(){
    return this->isPion;
}

/**
 * @brief Piece::getPieceAt
 * @param pieces
 * @param x
 * @param y
 * @return Piece
 */
Piece * Piece::getPieceAt(std::vector<Piece*> pieces, int x, int y){
    for(unsigned int i=0; i<pieces.size();i++){
        if(pieces[i]->getTabPosX()==x && pieces[i]->getTabPosY()==y){
            return pieces[i];
        }
    }
    return 0;
}

/**
 * @brief Piece::checkIfMate
 * @param x
 * @param y
 * @return bool
 */
bool Piece::checkIfMate(int x, int y){
    if(this->owner->getPiecesAt(x,y)){
        if(this->owner->getPiecesAt(x,y)->getOwner()!=this->owner){
            return true;
        }else
            return false;
    }else{
        return true;
    }
}

/**
 * @brief Piece::setImage
 * @param color
 */
void Piece::setImage(QString color){
    this->color = color;
}

/**
 * @brief Piece::getIsKing
 * @returnisKing
 */
bool Piece::getIsKing(){
    return this->isKing;
}

/**
 * @brief Piece::IsPossibleMove
 * @param x
 * @param y
 * @param possibleMove
 * @return bool
 */
bool Piece::IsPossibleMove(int x, int y, vector<QPoint> possibleMove){
    for(unsigned int i=0;i<possibleMove.size();i++)
    {
        if(QPoint(x,y)==possibleMove[i])
            return true;
    }
    return false;
}

/**
 * @brief Piece::updateAllPossibleMove
 * @param pieces
 */
void Piece::updateAllPossibleMove(vector<Piece *> pieces){

}

/**
 * @brief Piece::operator -
 * @param p
 * @return pos
 */
QPoint& Piece::operator -(const QPoint& p){
    pos.setX(abs(this->tabPosX-p.x()));
    pos.setY(abs(this->tabPosY-p.y()));
    cout << "x = " << this->tabPosX << " , y = " << this->tabPosY << endl;
    cout << " x = " << pos.x() << " , y = " << pos.y() << endl;
    return pos;
}
