#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QListWidget>
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
    void on_special_symbols_replacement_textChanged();

    void on_list_of_PL_itemDoubleClicked(QListWidgetItem *item);

    void on_list_of_PL_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_list_of_PL_add_item_clicked();

    void on_list_of_PL_del_item_clicked();

    void on_list_of_PL_item_view_stateChanged(int arg1);

    void on_table_mark_row_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
