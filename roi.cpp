#include "roi.h"

//_______________________________ROI_________________________________

/**
 * @brief Roi::Roi, constructor of the piece
 * @param parent
 * @param color
 * @param owner
 * @param width
 * @param height
 * @param x
 * @param y
 */
Roi::Roi(QWidget *parent, QString color,Playerjeu * owner, int width, int height, int x, int y)
{
    this->lbl = new QLabel(parent);
    this->lbl->setPixmap(QPixmap(":/images/Pieces/roi_blanc.png"));
    this->setImage(color);
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->lbl->move(x,y);
    this->owner = owner;
    this->isKing = true;
}


/**
 * @brief Roi::~Roi, destructor of the piece
 */
Roi::~Roi(){
    delete this->lbl;
}

//_______________________________METHOD_________________________________

/**
 * @brief Roi::move, movement of the king
 * @param x
 * @param y
 */
void Roi::move(int x,int y){
    this->lbl->move(x*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),y*TAILLECASE+CHESSBOARD_POS.y());
    this->setTabPosX(x);
    this->setTabPosY(y);
}


/**
 * @brief Roi::isValidMove , check if the movement is valid
 * @param x
 * @param y
 * @param pieces
 * @return
 */
bool Roi::isValidMove(int x,int y,std::vector<Piece*> pieces){
    if(abs(x-this->tabPosX)<=1 && abs(y-this->tabPosY)<=1 && this->moveInBoard(x,y) && (x!=this->tabPosX || y!=this->tabPosY) && this->checkIfMate(x,y))
        return true;
    else
        return false;
}

/**
 * @brief Roi::setImage, load the picture for the king
 * @param color
 */
void Roi::setImage(QString color){
    if(color == "Blanc"){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/roi_blanc.png")); //Image tour blanche
        this->namePiece = '6';
    }else if(color == "Noir"){
        this->lbl->setPixmap(QPixmap(":/images/Pieces/roi_noir.png"));  //Image tour noire
        this->namePiece = 'k';
    }
}


/**
 * @brief Roi::updateAllPossibleMove, check all positions for the king
 * @param pieces
 */
void Roi::updateAllPossibleMove(std::vector<Piece *> pieces){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(this->isValidMove(i,j,pieces)){
                this->allPossibleMove.push_back(QPoint(i,j));
            }
        }
    }
}

