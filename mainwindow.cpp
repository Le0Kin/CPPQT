#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>

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

/////////////// Задание 1 ///////////////

// Переменная "text_editor_undo_list" объявлена в файле "mainwindow.h"
void MainWindow::on_text_editor_editor_textChanged()
{
    QString text = ui->text_editor_editor->toPlainText();

    // Если контейнер изменений пуст, предыдущий текст не равен нынешнему
    // и последний символ не пробел, то добавляем изменение.
    if (text_editor_undo_list.isEmpty() ||
       (text_editor_undo_list.back() != text &&
        text.back() != ' '))
    {
        text_editor_undo_list.push_back( ui->text_editor_editor->toPlainText() );
    }
}

void MainWindow::on_text_editor_undo_clicked()
{
    // Если контейнер изменений не пуст, то берем из него последний текст, присваеваем текст полю и удаляем.
    if (!text_editor_undo_list.isEmpty())
    {
        ui->text_editor_editor->setPlainText( text_editor_undo_list.back() );
        text_editor_undo_list.pop_back();
    }
    // Иначе удаляем последний символ
    else
    {
        QString text = ui->text_editor_editor->toPlainText();
        text.remove( -1, 1 );
        ui->text_editor_editor->setPlainText( text );
    }
}
/////////////// Конец задания 1 ///////////////

void MainWindow::on_text_editor_info_clicked()
{
    QFile file (":/information/text_editor_info.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString message = stream.read(file.size());
        QMessageBox::information(this, "Информация о текстовом редакторе", message);
    }
}

void MainWindow::on_text_editor_save_txt_clicked()
{
    QFile file ("./text.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << ui->text_editor_editor->toPlainText();
        stream.flush();
    }
}

void MainWindow::on_text_editor_save_bin_clicked()
{
    // Переменная с автором
    QString author = "Author: " + ui->text_editor_author->text() + "\n\n";

    QFile file ("./text.bin");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << author << ui->text_editor_editor->toPlainText();
        stream.flush();
    }
}
