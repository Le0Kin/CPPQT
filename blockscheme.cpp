#include "blockscheme.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

int BlockScheme::now_geometry = 0;

BlockScheme::BlockScheme(QObject *parent) : QObject(parent), QGraphicsItem ()
{
    x = 0;
    y = 0;
    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    if (now_geometry == 0) {geometry = Geometry::RECTANGLE; now_geometry++;}
    else if (now_geometry == 1) {geometry = Geometry::ELLIPS; now_geometry++;}
    else if (now_geometry == 2) {geometry = Geometry::STAR; now_geometry = 0;}
    setPos(0,0);
    moving = false;
    scale = 1;
}

void BlockScheme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    if (geometry == Geometry::RECTANGLE) painter->drawRect(x, y, 200, 100);
    if (geometry == Geometry::ELLIPS) painter->drawEllipse(x, y, 200, 100);
    if (geometry == Geometry::STAR)
    {
        QPolygon polygon;
        polygon << QPoint(100, 0)   // Верх
                << QPoint(120, 40)  // Центр-право-верх
                << QPoint(200, 40)  // Право-верх
                << QPoint(140, 60)  // Центр-право-низ
                << QPoint(200, 100) // Право-низ
                << QPoint(100, 70)  // Центр-низ
                << QPoint(0, 100)   // Лево-низ
                << QPoint(60, 60)   // Центр-лево-низ
                << QPoint(0, 40)    // Лево-верх
                << QPoint(80, 40);  // Центр-лево-верх
        painter->drawPolygon(polygon);
    }
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF BlockScheme::boundingRect() const
{
    return QRectF(x, y, 200, 100);
}

void BlockScheme::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
    if (event->button() == Qt::LeftButton)
    {
        moving = true;
        bpoint = event->pos().toPoint();
    }
    if (event->button() == Qt::RightButton)
    {
        this->deleteLater();
        emit reDraw();
    }
    if (event->button() == Qt::MiddleButton)
    {
        this->setRotation(this->rotation() + 15);
    }
}

void BlockScheme::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    if (event->button() == Qt::LeftButton)
    {
        moving = false;
        emit reDraw();
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void BlockScheme::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving)
    {
        QPoint p = event->pos().toPoint() - bpoint;
        x += p.x();
        y += p.y();
        bpoint = event->pos().toPoint();
        emit reDraw();
    }
}

void BlockScheme::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit dblClick();
    }
}

void BlockScheme::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (event->delta() > 0)
    {
        scale += 0.1;
    }
    else
    {
        if (scale > 0.1) scale -= 0.1;
    }
    this->setScale(scale);
}
