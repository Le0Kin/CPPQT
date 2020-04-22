#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "blockscheme.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
//    QGraphicsView *view;
    QGraphicsScene *scence;
    BlockScheme *bscheme;
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void reDraw();
    void randomColorF();
};

#endif // MAINWINDOW_H
