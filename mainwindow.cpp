#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Загрузка окон
    ui->setupUi(this);
    st_window = new settings_window();

    // Загрузка перевода
    translator.load(":/languages/app_en_translate.qm");

    // Загрузка настроек
    settings = new QSettings("CppQtLearning", "CppQtHw4", this);
    loadSettings();

    // Перевод
    on_translate_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Загрузка настроек
void MainWindow::loadSettings()
{
    ui->new_file->setShortcut(              settings->value("new_file_key_hotkey", "Ctrl+N").toString());
    ui->open_file->setShortcut(             settings->value("open_file_key_hotkey", "Ctrl+O").toString());
    ui->open_file_readOnly->setShortcut(    settings->value("open_file_read_only_key_hotkey", "Ctrl+R").toString());
    ui->save_txt->setShortcut(              settings->value("save_file_txt_key_hotkey", "Ctrl+S").toString());
    ui->save_bin->setShortcut(              settings->value("save_file_bin_key_hotkey").toString());
    ui->quit->setShortcut(                  settings->value("quit_key_hotkey", "Ctrl+Q").toString());
    ui->translate->setShortcut(             settings->value("translate_key_hotkey", "Ctrl+T").toString());
    ui->settings->setShortcut(              settings->value("settings_key_hotkey").toString());
    ui->about->setShortcut(                 settings->value("about_key_hotkey").toString());

    translate =                             settings->value("translate", true).toBool();
}

// Создание файла
void MainWindow::on_new_file_triggered()
{
    ui->text_editor_editor->setPlainText("");
    ui->text_editor_editor->setReadOnly(0);
}

// Открытие файла
void MainWindow::on_open_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "./", "*.txt *.bin");
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        ui->text_editor_editor->setReadOnly(0);
        QTextStream stream(&file);
        ui->text_editor_editor->setPlainText( stream.read(file.size()) );
    }
}

// Открытие файла только для чтения
void MainWindow::on_open_file_readOnly_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл только для чтения"), "./", "*.txt *.bin");
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        ui->text_editor_editor->setReadOnly(1);
        QTextStream stream(&file);
        ui->text_editor_editor->setPlainText( stream.read(file.size()) );
    }
}

// Сохранение в txt
void MainWindow::on_save_txt_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .txt формате"), "./", "*.txt");

    QFile file (path);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << ui->text_editor_editor->toPlainText();
        stream.flush();
    }
}

// Сохранение в bin
void MainWindow::on_save_bin_triggered()
{
    QString author = tr("Автор: ") + ui->text_editor_author->text() + "\n\n";

    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .bin формате"), "./", "*.bin");

    QFile file (path);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << author << ui->text_editor_editor->toPlainText();
        stream.flush();
    }
}

// Справка
void MainWindow::on_about_triggered()
{
    QFile file (tr(":/information/text_editor_info_RU.txt"));
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString message = stream.read(file.size());
        QMessageBox::information(this, tr("Информация о текстовом редакторе"), message);
    }
}

// Кнопка отмены
void MainWindow::on_text_editor_undo_clicked()
{
    ui->text_editor_editor->undo();
}

// Перевод (false - eng)
void MainWindow::on_translate_triggered()
{
    if (translate == false)
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        st_window->translate();
        settings->setValue("translate", false);
        translate = !translate;
    }
    else
    {
        qApp->removeTranslator(&translator);
        ui->retranslateUi(this);
        st_window->translate();
        settings->setValue("translate", true);
        translate = !translate;
    }
}

// Выход
void MainWindow::on_quit_triggered()
{
    qApp->exit();
}

// Настройки
void MainWindow::on_settings_triggered()
{
    st_window->exec();
    loadSettings();
}
