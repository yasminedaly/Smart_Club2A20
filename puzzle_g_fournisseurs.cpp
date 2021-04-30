#include "puzzle_g_fournisseurs.h"
#include "pieces_g_fournisseurs.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
Puzzle_G_Fournisseurs::Puzzle_G_Fournisseurs(int imageSize, QWidget *parent)
    : QWidget(parent), m_ImageSize(imageSize)
{
    setAcceptDrops(true);
    setMinimumSize(m_ImageSize, m_ImageSize);
    setMaximumSize(m_ImageSize, m_ImageSize);
}

void Puzzle_G_Fournisseurs::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void Puzzle_G_Fournisseurs::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType()))
        event->accept();
    else
        event->ignore();
}

void Puzzle_G_Fournisseurs::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void Puzzle_G_Fournisseurs::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType())
        && pieceRects.indexOf(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void Puzzle_G_Fournisseurs::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType())
        && pieceRects.indexOf(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data(Pieces_G_Fournisseurs::puzzleMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize())) {
            inPlace++;
            if (inPlace == 25)
                emit puzzleCompleted();
        }
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

void Puzzle_G_Fournisseurs::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = pieceRects.indexOf(square);

    if (found == -1)
        return;

    QPoint location = pieceLocations[found];
    QPixmap pixmap = piecePixmaps[found];
    pieceLocations.removeAt(found);
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);

    if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
        inPlace--;

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(Pieces_G_Fournisseurs::puzzleMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        pieceLocations.insert(found, location);
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);
        update(targetSquare(event->pos()));

        if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
            inPlace++;
    }
}

void Puzzle_G_Fournisseurs::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i)
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    painter.end();
}

const QRect Puzzle_G_Fournisseurs::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/pieceSize() * pieceSize(), position.y()/pieceSize() * pieceSize(), pieceSize(), pieceSize());
}

int Puzzle_G_Fournisseurs::pieceSize() const
{
    return m_ImageSize / 5;
}

int Puzzle_G_Fournisseurs::imageSize() const
{
    return m_ImageSize;
}
