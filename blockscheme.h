#ifndef BLOCKSCHEME_H
#define BLOCKSCHEME_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>


class BlockScheme : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:
    explicit BlockScheme(QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
    static int now_geometry;

signals:
    void reDraw();
    void dblClick();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    enum Geometry {RECTANGLE, ELLIPS, STAR};
    int x, y;
    Geometry geometry;
    QPoint bpoint;
    bool moving;
    QBrush brush;
    float scale;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent  *event)  override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)  override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
};

#endif // BLOCKSCHEME_H
