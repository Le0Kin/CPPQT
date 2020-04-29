#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);
    model->setRootPath("");
    model->setFilter(QDir::AllEntries | QDir::NoDot);
    ui->FM_window->setModel(model);

    fc = new find_confugation();
    check_change_disk_timer = new QTimer;
    connect(check_change_disk_timer, SIGNAL(timeout()), fc, SLOT(check()));
    check_change_disk_timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FM_window_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileinfo = model->fileInfo(index);
    QDir dir = fileinfo.dir();
    if (fileinfo.fileName() == "..")
    {
        dir.cdUp();
        ui->FM_window->setRootIndex(model->index(dir.absolutePath()));
        ui->FM_path->setText(dir.absolutePath());
    }
    else if (fileinfo.isDir())
    {
        ui->FM_window->setRootIndex(index);
        ui->FM_path->setText(dir.absolutePath());
    }
}

void MainWindow::on_FM_home_clicked()
{
    ui->FM_window->setRootIndex(model->index(""));
    ui->FM_path->setText("");
}

void MainWindow::on_FM_path_editingFinished()
{
    QString path = ui->FM_path->text();
    ui->FM_window->setRootIndex(model->index(path));
}
