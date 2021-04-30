#ifndef PIECES_G_FOURNISSEURS_H
#define PIECES_G_FOURNISSEURS_H

#include <QListWidget>
class Pieces_G_Fournisseurs : public QListWidget
{
    Q_OBJECT
public:
    explicit Pieces_G_Fournisseurs(int pieceSize, QWidget *parent = 0);
    void addPiece(QPixmap pixmap, QPoint location);

    static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

    int m_PieceSize;
};

#endif // PIECES_G_FOURNISSEURS_H
