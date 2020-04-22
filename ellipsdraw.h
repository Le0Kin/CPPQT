#ifndef ELLIPSDRAW_H
#define ELLIPSDRAW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class EllipsDraw : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ boundingRect WRITE setRectF)
public:
    explicit EllipsDraw(QObject *parent = nullptr);

public slots:
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent  *event)  override;
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRectF(QRectF rect) {this->rect = rect;}
private:
    QRectF rect;
};

#endif // ELLIPSDRAW_H
