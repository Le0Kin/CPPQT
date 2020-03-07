#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_QuadEquation_button_clicked();

    void on_SideOfATriangle_button_clicked();

    void on_Quest3_set_default_text_clicked();

    void on_Quest3_set_text_of_text_line_clicked();

    void on_Quest3_set_text_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
