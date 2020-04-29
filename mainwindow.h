#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

// Перевод
#include <QTranslator>

// Справка
#include <QMessageBox>

// Работа с файлами
#include <QTextStream>
#include <QFileDialog>

// Печать
#include <QPrinter>
#include <QPrintDialog>

// Таблицы
#include <QListWidget>
#include <QSpinBox>
#include <QTextTable>

// Тулбар
#include <QToolBar>

// Форматирование текста
#include <QFontDialog>

// Дата и время
#include <QDateTime>

// Дополнительные классы
#include "menu_table_layout.h"
#include "pushbutton_actionwidget.h"

// Дополнительные формы
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
    void on_print_triggered();
    void on_text_editor_editor_textChanged();
    void menu_button_change_font_text_clicked();


    void add_table_function();
    void tab_close(int index);
    void save_format_slot();
    void apply_format_slot();
    void text_aligment_left_slot();
    void text_aligment_center_slot();
    void text_aligment_right_slot();

    void on_add_time_triggered();

    void on_add_date_triggered();

    void on_add_date_and_time_triggered();

private:
    Ui::MainWindow *ui;
    settings_window *st_window;
    QToolBar *tb;

    QSettings *settings;
    QTranslator translator;
    bool translate;

    enum style { light = 0, dark = 1, yellow = 2 , blue = 3 };

    void setStyleSheet(style s);
    void load_settings();

    menu_table_layout *width_new_table;
    menu_table_layout *height_new_table;

    QTextCharFormat saved_format;
};



#endif // MAINWINDOW_H
