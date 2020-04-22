#include "mainwindow.h"
#include <QMessageBox>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{    
    srand(clock());
    scence = new QGraphicsScene(this);
    setScene(scence);
    bscheme = new BlockScheme(this);
    scence->addItem(bscheme);

    connect(bscheme, SIGNAL(reDraw()), this, SLOT(reDraw()));
    connect(bscheme, SIGNAL(dblClick()), this, SLOT(randomColorF()));
}
MainWindow::~MainWindow(){}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsItem *item = QGraphicsView::itemAt(event->pos());
    if (event->button() == Qt::LeftButton && !item)
    {
        bscheme = new BlockScheme(this);
        connect(bscheme, SIGNAL(reDraw()), this, SLOT(reDraw()));
        connect(bscheme, SIGNAL(dblClick()), this, SLOT(randomColorF()));
        scence->addItem(bscheme);
    }
}

void MainWindow::reDraw()
{
    scence->update();
    update();
}

void MainWindow::randomColorF()
{
    bscheme->setBrush(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
}

