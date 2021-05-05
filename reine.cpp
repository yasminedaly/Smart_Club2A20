#include "reine.h"
#include "iostream"
using namespace std;

//_______________________________REINE_________________________________
/**
 * @brief Reine::Reine, constructor of the queen
 * @param parent
 * @param color
 * @param owner
 * @param width
 * @param height
 * @param x
 * @param y
 */
Reine::Reine(QWidget *parent, QString color,Playerjeu * owner, int width, int height, int x,int y)
{
    this->lbl = new QLabel(parent);
    this->setImage(color);
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->lbl->move(x,y);
    this->owner = owner;
    this->lbl->setVisible(true);
}

/**
 * @brief Reine::~Reine, destructor of the queen
 */
Reine::~Reine(){
    delete this->lbl;
}
//_______________________________METHOD_________________________________

/**
 * @brief Reine::setImage, load the picture of the piece
 * @param color
 */
void Reine::setImage(QString color){
    if(color==("Blanc")){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/reine_blanc.png")); //Image reine blanche
        this->namePiece = '5';
    }else if(color==("Noir")){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/reine_noir.png"));  //Image reine noire
        this->namePiece = 'q';
    }
}


/**
 * @brief Reine::move, movement of the queen
 * @param x
 * @param y
 */
void Reine::move(int x, int y){
    this->lbl->move(x*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),y*TAILLECASE+CHESSBOARD_POS.y());
    this->setTabPosX(x);
    this->setTabPosY(y);
}


/**
 * @brief Reine::isValidMove, check if the movement is possible
 * @param x
 * @param y
 * @param pieces
 * @return
 */
bool Reine::isValidMove(int x, int y,std::vector<Piece*> pieces){
    if(( this->checkIfMate(x,y) && ((x!=this->tabPosX*TAILLECASE && y==this->tabPosY) && this->moveInBoard(x,y) ||
        (abs(x-this->tabPosX)==abs(y-this->tabPosY)) || (x==this->tabPosX && y != this->tabPosY)&& 
         this->moveInBoard(x,y) ) && (x!=this->tabPosX || y!=this->tabPosY) ) && this->IsPossibleMove(x,y,this->allPossibleMove))
        
        return true;
    else
        return false;
}

/**
 * @brief Reine::updateAllPossibleMove, check all movement possible
 * @param pieces
 */

void Reine::updateAllPossibleMove(std::vector<Piece*> pieces){
    int i=this->tabPosX-1,j=this->tabPosY-1;
    bool alreadyHasEnemy = false;

    while(this->moveInBoard(i,j)){
        if(!this->checkIfMate(i,j) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,i,j) && this->getPieceAt(pieces,i,j)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(i,j));
        }
        i--;
        j--;
    }

    i=this->tabPosX-1,j=this->tabPosY+1;
    alreadyHasEnemy = false;
    while(this->moveInBoard(i,j)){
        if(!this->checkIfMate(i,j) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,i,j) && this->getPieceAt(pieces,i,j)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(i,j));
        }
        i--;
        j++;
    }

    i=this->tabPosX+1,j=this->tabPosY-1;
    alreadyHasEnemy = false;
    while(this->moveInBoard(i,j)){
        if(!this->checkIfMate(i,j) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,i,j) && this->getPieceAt(pieces,i,j)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(i,j));
        }
        i++;
        j--;
    }

    i=this->tabPosX+1,j=this->tabPosY+1;
    alreadyHasEnemy = false;
    while(this->moveInBoard(i,j)){
        if(!this->checkIfMate(i,j) || alreadyHasEnemy)
        {
            break;
        }else{
            if(this->getPieceAt(pieces,i,j) && this->getPieceAt(pieces,i,j)->getOwner()!=this->owner)
                alreadyHasEnemy = true;
            this->allPossibleMove.push_back(QPoint(i,j));
        }
        i++;
        j++;
    }

     i=this->tabPosX-1,j=this->tabPosX+1;
     alreadyHasEnemy = false;
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

/*bool Reine::IsPossibleMove(int x, int y, vector<QPoint> possibleMove){
    for(int i=0;i<possibleMove.size();i++)
    {
        if(QPoint(x,y)==possibleMove[i])
            return true;
    }
    return false;
}*/
