#include "ellipsdraw.h"
#include <QPainter>

EllipsDraw::EllipsDraw(QObject *parent) : QObject(parent), QGraphicsItem()
{

}

void EllipsDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(0, 0, 100, 100);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
QRectF EllipsDraw::boundingRect() const
{
    /* возвращаем координаты расположения точки
     * по ним будет определяться нажатие точки
     * */
    return QRectF(0,0,100,100);
}
