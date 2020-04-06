#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>

#include "settings.h"

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

    void on_open_file_readOnly_triggered();

    void on_open_file_triggered();

    void on_new_file_triggered();

    void on_save_txt_triggered();

    void on_save_bin_triggered();

    void on_about_triggered();

    void on_text_editor_undo_clicked();

    void on_translate_triggered();

    void on_quit_triggered();

    void on_settings_triggered();

private:
    Ui::MainWindow *ui;
    settings_window *st_window;

    QSettings *settings;
    QTranslator translator;
    bool translate;

    void setStyleSheet(int index);
    void loadSettings();
};



#endif // MAINWINDOW_H
