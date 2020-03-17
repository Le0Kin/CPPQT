#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regular_expression.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
////////////////////// Задание 1 //////////////////////
void MainWindow::on_special_symbols_replacement_textChanged()
{
    regular_expression::find_and_replace(ui->special_symbols_replacement);
}
////////////////////// Конец задания 1 //////////////////////

////////////////////// Задание 2 //////////////////////
// При двойном клике на элемент списка включается изменение текста
void MainWindow::on_list_of_PL_itemDoubleClicked(QListWidgetItem *item)
{
    ui->list_of_PL->openPersistentEditor(item);
}
// При смене выделенного элемента в списке выключается изменение текста на предыдущем выбраном элементе
void MainWindow::on_list_of_PL_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->list_of_PL->closePersistentEditor(previous);
}
// Добавление элемента в список со стандартным значком, только если есть название
void MainWindow::on_list_of_PL_add_item_clicked()
{
    QString text = ui->list_of_PL_line_edit->text();
    if (text != "")
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/default_logo.png"), text);
        ui->list_of_PL->addItem(item);
        ui->list_of_PL_line_edit->setText("");
    }
}
// Удаление элемента из списка
void MainWindow::on_list_of_PL_del_item_clicked()
{
    QListWidgetItem *currentItem = ui->list_of_PL->currentItem();
    ui->list_of_PL->removeItemWidget(currentItem);
    delete currentItem;
}
// При изменении состояния checkbox'а проверяется его состояние, если он включен, то ставим режим отображения иконками, иначе списком
void MainWindow::on_list_of_PL_item_view_stateChanged(int arg1)
{
    if (arg1)   { ui->list_of_PL->setViewMode(QListView::IconMode); }
    else        { ui->list_of_PL->setViewMode(QListView::ListMode); }
}
////////////////////// Конец задания 2 //////////////////////

////////////////////// Задание 3 //////////////////////
void MainWindow::on_table_mark_row_clicked()
{
    quint32 current_row = ui->table->currentRow();
    quint32 count_of_column = ui->table->columnCount();

    for (int i = 0; i < count_of_column; i++) {
        ui->table->item(current_row, i)->setBackgroundColor(QColor(227,207,219));
    }
}
////////////////////// Конец задания 3 //////////////////////
