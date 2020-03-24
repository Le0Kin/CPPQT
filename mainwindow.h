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

    void on_text_editor_editor_textChanged();

    void on_text_editor_undo_clicked();

    void on_text_editor_info_clicked();

    void on_text_editor_save_txt_clicked();

    void on_text_editor_save_bin_clicked();

private:
    Ui::MainWindow *ui;

    // Глобальные переменные
    QList<QString> text_editor_undo_list;
};



#endif // MAINWINDOW_H
