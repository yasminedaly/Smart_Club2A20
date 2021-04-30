#include "playerjeu.h"
#include "mainwindow.h"
#include "mainmenu.h"

//_______________________________PLAYER_________________________________

/**
 * @brief Player::Player, constructor of a player
 * @param id
 */
Playerjeu::Playerjeu(int id)
{
    this->id = id;
}

//_______________________________METHOD_________________________________

/**
 * @brief Player::setHasPlayed, check if the player has played
 * @param hasPlayed
 */
void Playerjeu::setHasPlayed(bool hasPlayed)
{
    this->hasPlayed = hasPlayed;
}

/**
 * @brief Player::getHasPlayed
 * @return bool
 */
bool Playerjeu::getHasPlayed()
{
    return this->hasPlayed;
}

/**
 * @brief Player::getId
 * @return int
 */
int Playerjeu::getId()
{
    return this->id;
}

/**
 * @brief Player::removePiece
 * @param piece
 */
void Playerjeu::removePiece(Piece  *piece)
{    
    for(std::vector<Piece *>::iterator it = this->pieces.begin() ; it < this->pieces.end(); it++)
        if(piece==*it){
            this->pieces.erase(it);
        }
}


/**
 * @brief Player::addPiece
 * @param piece
 */
void Playerjeu::addPiece(Piece * piece){
    this->pieces.push_back(piece);
}


/**
 * @brief Player::getPieces
 * @return vector<Pieces>
 */
vector<Piece *> Playerjeu::getPieces(){
    return this->pieces;
}

/**
 * @brief Player::getPiecesAt a position
 * @param x
 * @param y
 * @return Piece
 */
Piece * Playerjeu::getPiecesAt(int x, int y){
    for(unsigned int i=0; i<this->pieces.size();i++){
        if(pieces[i]->getTabPosX()==x && pieces[i]->getTabPosY()==y){
            return this->pieces[i];
        }
    }
}
