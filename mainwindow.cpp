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
    settings = new QSettings("CppQtLearning", "CppQt", this);
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

    setStyleSheet(                          settings->value("styleSheet_index", 0).toInt());
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

// Применение таблицы стилей (0-светлый, 1-темный, 2-желтый, 3-синий)
void MainWindow::setStyleSheet(int index)
{
    switch (index) {
    case 0:
        qApp->setStyleSheet("MainWindow                 { background-color: #f0f0f0; color: #000;                            }"
                            "settings_window            { background-color: #f0f0f0; color: #000;                            }"
                            "QMenuBar                   { background-color: #f0f0f0; color: #000;                            }"
                            "QMenu                      { background-color: #f0f0f0; color: #000;                            }"
                            "QLabel                     { color: #000;                                                       }"
                            "QLineEdit                  { background-color: #ffffff; color: #000; border: 1px solid #a8a8a8; }"
                            "QPlainTextEdit             { background-color: #ffffff; color: #000; border: 1px solid #a8a8a8; }"
                            "QPushButton                { background-color: #e1e1e1; color: #000; border: 1px solid #a8a8a8; }"
                            "QComboBox                  { background-color: #e1e1e1; color: #000;                            }"
                            "QComboBox::drop-arrow      { background-color: #e1e1e1; color: #000;                            }"
                            "QComboBox QAbstractItemView{ background-color: #e1e1e1; color: #000;                            }");
        break;
    case 1:
        qApp->setStyleSheet("MainWindow                 { background-color: #101010; color: #fff;                            }"
                            "settings_window            { background-color: #101010; color: #fff;                            }"
                            "QMenuBar                   { background-color: #101010; color: #fff;                            }"
                            "QMenu                      { background-color: #101010; color: #fff;                            }"
                            "QLabel                     { color: #fff;                                                       }"
                            "QLineEdit                  { background-color: #404040; color: #fff; border: 1px solid #606060; }"
                            "QPlainTextEdit             { background-color: #404040; color: #fff; border: 1px solid #606060; }"
                            "QPushButton                { background-color: #404040; color: #fff; border: 1px solid #606060; }"
                            "QComboBox                  { background-color: #404040; color: #fff;                            }"
                            "QComboBox::drop-arrow      { background-color: #404040; color: #fff;                            }"
                            "QComboBox QAbstractItemView{ background-color: #404040; color: #fff;                            }");
        break;
    case 2:
        qApp->setStyleSheet("MainWindow                 { background-color: #101010; color: yellow;                            }"
                            "settings_window            { background-color: #101010; color: yellow;                            }"
                            "QMenuBar                   { background-color: #101010; color: yellow;                            }"
                            "QMenu                      { background-color: #101010; color: yellow;                            }"
                            "QLabel                     { color: yellow;                                                       }"
                            "QLineEdit                  { background-color: #000000; color: yellow; border: 1px solid #606060; }"
                            "QPlainTextEdit             { background-color: #000000; color: yellow; border: 1px solid #606060; }"
                            "QPushButton                { background-color: #404040; color: yellow; border: 1px solid #606060; }"
                            "QComboBox                  { background-color: #404040; color: yellow;                            }"
                            "QComboBox::drop-arrow      { background-color: #404040; color: yellow;                            }"
                            "QComboBox QAbstractItemView{ background-color: #404040; color: yellow;                            }");
        break;
    case 3:
        qApp->setStyleSheet("MainWindow                 { background-color: #a3def8; color: #000;                            }"
                            "settings_window            { background-color: #a3def8; color: #000;                            }"
                            "QMenuBar                   { background-color: #a3def8; color: #000;                            }"
                            "QMenu                      { background-color: #a3def8; color: #000;                            }"
                            "QLabel                     { color: #000;                                                       }"
                            "QLineEdit                  { background-color: #269dce; color: #000; border: 1px solid #606060; }"
                            "QPlainTextEdit             { background-color: #269dce; color: #000; border: 1px solid #606060; }"
                            "QPushButton                { background-color: #269dce; color: #000; border: 1px solid #606060; }"
                            "QComboBox                  { background-color: #269dce; color: #000;                            }"
                            "QComboBox::drop-arrow      { background-color: #269dce; color: #000;                            }"
                            "QComboBox QAbstractItemView{ background-color: #269dce; color: #000;                            }");
        break;
    default:
        break;
    }
}
