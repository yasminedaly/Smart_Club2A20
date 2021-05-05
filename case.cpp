#include "case.h"

//_______________________________CASE_________________________________

/**
 * @brief Case::Case constructor of the class Case
 * @param size
 * @param xPos
 * @param yPos
 */
Case::Case(int size, int xPos, int yPos)
{
    this->size = size;
    this->xPos = xPos+CHESSBOARD_POS.x();
    this->yPos = yPos+CHESSBOARD_POS.y();
}

//_______________________________METHOD_________________________________

/**
 * @brief Case::draw method to draw a case with a color in parameter
 * @param painter
 * @param color
 */
void Case::draw(QPainter *painter, QColor color)
{
    QRect r1(this->xPos,this->yPos,this->size,this->size);
    painter->setPen(Qt::black);
    painter->setBrush(color);
    painter->drawRect(r1);
}
