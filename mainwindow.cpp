#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Создание окон и меню
    ui->setupUi(this);
    st_window = new settings_window();
    ui->text_editor_tab_widget->tabBar()->setTabsClosable(true);
    connect(ui->text_editor_tab_widget->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(tabClose(int)));

    // Создание меню в кнопке создания таблиц
    width_new_table = new menu_table_layout(tr("Ширина таблицы"));
    height_new_table = new menu_table_layout(tr("Высота таблицы"));
    QPushButton *add_table = new QPushButton(tr("Добавить таблицу"));
    pushButton_actionWidget *add_table_button = new pushButton_actionWidget(add_table);

    connect(add_table, SIGNAL(clicked()), this, SLOT(add_table_function()));

    QMenu *menu = new QMenu();
    menu->addAction(width_new_table);
    menu->addAction(height_new_table);
    menu->addAction(add_table_button);
    ui->text_editor_add_table->setMenu(menu);

    // Загрузка перевода
    translator.load(":/languages/app_en_translate.qm");

    // Загрузка настроек
    settings = new QSettings();
    load_settings();

    // Перевод
    on_translate_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Загрузка настроек
void MainWindow::load_settings()
{
    // Горячие клавиши
    ui->new_file->setShortcut(              settings->value("new_file_key_hotkey", "Ctrl+N").toString());
    ui->open_file->setShortcut(             settings->value("open_file_key_hotkey", "Ctrl+O").toString());
    ui->open_file_readOnly->setShortcut(    settings->value("open_file_read_only_key_hotkey", "Ctrl+R").toString());
    ui->save_txt->setShortcut(              settings->value("save_file_txt_key_hotkey", "Ctrl+S").toString());
    ui->save_bin->setShortcut(              settings->value("save_file_bin_key_hotkey").toString());
    ui->print->setShortcut(                 settings->value("print_file_hotkey", "Ctrl+P").toString());
    ui->quit->setShortcut(                  settings->value("quit_key_hotkey", "Ctrl+Q").toString());
    ui->translate->setShortcut(             settings->value("translate_key_hotkey", "Ctrl+T").toString());
    ui->settings->setShortcut(              settings->value("settings_key_hotkey").toString());
    ui->about->setShortcut(                 settings->value("about_key_hotkey").toString());

    // Перевод
    translate = settings->value("translate", true).toBool();

    // Стили
    int s = settings->value("styleSheet_index", style::light).toInt();
    setStyleSheet(static_cast<style>(s));
}

// Применение таблицы стилей
void MainWindow::setStyleSheet(style s)
{
    QFile file;
    QTextStream stream(&file);

    switch (s) {
    case style::light:
        file.setFileName(":/styles/style_light.css");
        break;
    case style::dark:
        file.setFileName(":/styles/style_dark.css");
        break;
    case style::yellow:
        file.setFileName(":/styles/style_yellow.css");
        break;
    case style::blue:
        file.setFileName(":/styles/style_blue.css");
        break;
    default:
        break;
    }

    file.open(QIODevice::ReadOnly);
    qApp->setStyleSheet(QString(stream.read(file.size())));
}

// Разделение абзацев горизонтальной линией
void MainWindow::on_text_editor_editor_textChanged()
{
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QString text = textWidget->toHtml();
    QTextCursor cursor = textWidget->textCursor();

    QRegExp reg_exp("</p>\n<p style=\" margin");
    if (text.contains(QRegExp(reg_exp)))
    {
        text.replace(QRegExp(reg_exp), "</p><hr>\n<p style=\" margin");
        textWidget->setHtml(text);

        cursor.movePosition(QTextCursor::Right);
        textWidget->setTextCursor(cursor);
    }
}

// Закрытие вкладки
void MainWindow::tabClose(int index)
{
    ui->text_editor_tab_widget->removeTab(index);
}


// Новый файл
void MainWindow::on_new_file_triggered()
{
    int index = ui->text_editor_tab_widget->addTab(new QTextEdit(), "new");
    ui->text_editor_tab_widget->setCurrentIndex(index);
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

    textWidget->setPlainText("");
    textWidget->setReadOnly(0);
}

// Открытие файла
void MainWindow::on_open_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "./", "*.txt *.bin");
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        int index = ui->text_editor_tab_widget->addTab(new QTextEdit(), file.fileName());
        ui->text_editor_tab_widget->setCurrentIndex(index);
        QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

        QTextStream stream(&file);

        textWidget->setReadOnly(0);
        textWidget->setPlainText( stream.read(file.size()) );
    }
}

// Открытие файла только для чтения
void MainWindow::on_open_file_readOnly_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл только для чтения"), "./", "*.txt *.bin");
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        int index = ui->text_editor_tab_widget->addTab(new QTextEdit(), file.fileName());
        ui->text_editor_tab_widget->setCurrentIndex(index);
        QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

        QTextStream stream(&file);

        textWidget->setReadOnly(1);
        textWidget->setPlainText( stream.read(file.size()) );
    }
}

// Сохранение в txt
void MainWindow::on_save_txt_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() != -1)
    {
        QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .txt формате"), "./", "*.txt");

        QFile file (path);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
            stream << textWidget->toPlainText();
            stream.flush();
        }
    }
}

// Сохранение в bin
void MainWindow::on_save_bin_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() != -1)
    {
        QString author = tr("Автор: ") + ui->text_editor_author->text() + "\n\n";

        QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .bin формате"), "./", "*.bin");

        QFile file (path);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
            stream << author << textWidget->toPlainText();
            stream.flush();
        }
    }
}

// Справка
void MainWindow::on_about_triggered()
{
    QFile file (tr(":/information/assets/text_editor_info/text_editor_info_EN.txt"));
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString message = stream.read(file.size());
        QMessageBox::information(this, tr("Информация о текстовом редакторе"), message);
    }
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

// Принтер
void MainWindow::on_print_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() != -1)
    {
        QPrinter printer;
        QPrintDialog *print_dialog = new QPrintDialog(&printer);
        print_dialog->setWindowTitle(tr("Печать"));
        QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

        if (print_dialog->exec() != QDialog::Accepted)
            return;

        textWidget->print(&printer);
    }
}

// Настройки
void MainWindow::on_settings_triggered()
{
    st_window->exec();
    load_settings();
}

// Кнопка отмены
void MainWindow::on_text_editor_undo_clicked()
{
    if (ui->text_editor_tab_widget->currentIndex() != -1)
    {
        QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
        textWidget->undo();
    }
}

// Создание таблицы
void MainWindow::add_table_function()
{
    if (ui->text_editor_tab_widget->currentIndex() != -1)
    {
        QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
        QTextCursor cursor = textWidget->textCursor();
        cursor.insertTable(height_new_table->get_number(),
                           width_new_table->get_number());
    }
}
