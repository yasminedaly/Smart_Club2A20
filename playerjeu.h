#ifndef PLAYERJEU_H
#define PLAYERJEU_H
#include "piece.h"

using namespace std;
class Playerjeu
{
public:
    Playerjeu(int id);
    void removePiece(Piece *piece);
    void addPiece(Piece * piece);
    void playPiece();
    vector<Piece *> getPieces();
    Piece * getPiecesAt(int x, int y);

    //getteur setteur asplay
    bool getHasPlayed();
    void setHasPlayed(bool hasPlayed);
    int getId();

private:
    vector<Piece *>  pieces ; //collection de piece
    int id; //identifiant joueur
    bool hasPlayed;
};

#endif // PLAYERJEU_H
