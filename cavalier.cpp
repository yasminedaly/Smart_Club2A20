#include "cavalier.h"
//_______________________________CAVALIER_________________________________

/**
 * @brief Cavalier::Cavalier, constructor of a Cavalier
 * @param parent
 * @param color
 * @param owner
 * @param width width of the piece
 * @param height height of the piece
 * @param x position x
 * @param y position y
 */
Cavalier::Cavalier(QWidget *parent, QString color, Playerjeu * owner , int width, int height, int x,int y)
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
 * @brief Cavalier::~Cavalier, destructor of the piece
 */
Cavalier::~Cavalier(){
    delete this->lbl;
}


//_______________________________METHOD_________________________________

/**
 * @brief Cavalier::setImage, load the picture of the piece
 * @param color
 */
void Cavalier::setImage(QString color){
    if(color==("Blanc")){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/cavalier_blanc.png")); //Image tour blanche
        this->namePiece = '2';
    }else if(color==("Noir")){
       this->lbl->setPixmap(QPixmap(":/images/Pieces/cavalier_noir.png"));  //Image tour noire;
        this->namePiece = 'c';
    }
}


/**
 * @brief Cavalier::move, movement of the piece
 * @param x
 * @param y
 */
void Cavalier::move(int x, int y){
    this->lbl->move(x*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),y*TAILLECASE+CHESSBOARD_POS.y());
    this->setTabPosX(x);
    this->setTabPosY(y);
}


/**
 * @brief Cavalier::isValidMove, check if we can mave the cavalier
 * @param x
 * @param y
 * @param pieces
 * @return boolean
 */
bool Cavalier::isValidMove(int x, int y,std::vector<Piece*> pieces){
    if((abs(x-this->tabPosX)==2 && abs(y-this->tabPosY)==1 || abs(x-this->tabPosX)==1 && abs(y-this->tabPosY)==2) 
       && this->moveInBoard(x,y) && this->checkIfMate(x,y))
        return true;
    else
        return false;
}




void Cavalier::updateAllPossibleMove(std::vector<Piece *> pieces){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(this->isValidMove(i,j,pieces))
                    this->allPossibleMove.push_back(QPoint(i,j));
        }
    }
}
