#include "pieces_g_fournisseurs.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

Pieces_G_Fournisseurs::Pieces_G_Fournisseurs(int pieceSize, QWidget *parent)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
        setDragEnabled(true);
        setViewMode(QListView::IconMode);
        setIconSize(QSize(m_PieceSize, m_PieceSize));
        setSpacing(10);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
}
void Pieces_G_Fournisseurs::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType()))
        event->accept();
    else
        event->ignore();
}

void Pieces_G_Fournisseurs::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType())) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void Pieces_G_Fournisseurs::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(Pieces_G_Fournisseurs::puzzleMimeType())) {
        QByteArray pieceData = event->mimeData()->data(Pieces_G_Fournisseurs::puzzleMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        addPiece(pixmap, location);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void Pieces_G_Fournisseurs::addPiece(QPixmap pixmap, QPoint location)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void Pieces_G_Fournisseurs::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(Pieces_G_Fournisseurs::puzzleMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
}
