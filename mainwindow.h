#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_FM_window_doubleClicked(const QModelIndex &index);

    void on_FM_home_clicked();

    void on_FM_path_editingFinished();

private:
    Ui::MainWindow *ui;

    QFileSystemModel *model;
};
#endif // MAINWINDOW_H
