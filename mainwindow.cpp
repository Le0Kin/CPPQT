#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "ui_settings.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Загрузка перевода
    translator.load(":/languages/app_en_translate.qm");

    // Создание окон и меню
    ui->setupUi(this);
    st_window = new settings_window();
    ui->text_editor_tab_widget->tabBar()->setTabsClosable(true);
    connect(ui->text_editor_tab_widget->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(tab_close(int)));

    // Создание меню для таблиц
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

    // Меню форматирования текста
    tb = addToolBar("ToolBar");
    tb->setMovable(false);

    QPushButton *menu_button_format_text = new QPushButton(tr("Форматирование текста"));
    QMenu *menu_format_text = new QMenu;
    menu_button_format_text->setMenu(menu_format_text);
    QAction *save_format = new QAction(tr("Сохранить формат выделеного текста"));
    QAction *apply_format = new QAction(tr("Применить сохраненный формат на выделенногом тексте"));
    connect(save_format, SIGNAL(triggered()), this, SLOT(save_format_slot()));
    connect(apply_format, SIGNAL(triggered()), this, SLOT(apply_format_slot()));
    menu_format_text->addAction(save_format);
    menu_format_text->addAction(apply_format);

    QPushButton *menu_button_aligment_text = new QPushButton(tr("Выравнивание текста"));
    QMenu *menu_aligment_text = new QMenu;
    menu_button_aligment_text->setMenu(menu_aligment_text);
    QAction *text_aligment_left = new QAction(tr("По левому краю"));
    QAction *text_aligment_center = new QAction(tr("По центру"));
    QAction *text_aligment_right = new QAction(tr("По правому краю"));
    connect(text_aligment_left, SIGNAL(triggered()), this, SLOT(text_aligment_left_slot()));
    connect(text_aligment_center, SIGNAL(triggered()), this, SLOT(text_aligment_center_slot()));
    connect(text_aligment_right, SIGNAL(triggered()), this, SLOT(text_aligment_right_slot()));
    menu_aligment_text->addAction(text_aligment_left);
    menu_aligment_text->addAction(text_aligment_center);
    menu_aligment_text->addAction(text_aligment_right);

    QPushButton *menu_button_change_font_text = new QPushButton(tr("Установить шрифт"));
    connect(menu_button_change_font_text, SIGNAL(clicked()), this, SLOT(menu_button_change_font_text_clicked()));

    tb->addWidget(menu_button_format_text);
    tb->addWidget(menu_button_aligment_text);
    tb->addWidget(menu_button_change_font_text);

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

QTextEdit& MainWindow::getTextEditor() const
{
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    return *textWidget;
}

QAction &MainWindow::getAddDateButton() const
{
    return *(ui->add_date);
}

QAction &MainWindow::getNewFileButton() const
{
    return *(ui->new_file);
}

// Загрузка настроек
void MainWindow::load_settings() {
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
void MainWindow::setStyleSheet(style s) {
    QFile file;
    QTextStream stream(&file);

    switch (s) {
    case style::light:  file.setFileName(":/styles/style_light.css"); break;
    case style::dark:   file.setFileName(":/styles/style_dark.css"); break;
    case style::yellow: file.setFileName(":/styles/style_yellow.css"); break;
    case style::blue:   file.setFileName(":/styles/style_blue.css"); break;
    default: break;
    }

    if (!file.open(QIODevice::ReadOnly)) return;
    qApp->setStyleSheet(QString(stream.read(file.size())));
}

// Разделение абзацев горизонтальной линией
void MainWindow::on_text_editor_editor_textChanged() {
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QString text = textWidget->toHtml();
    QTextCursor cursor = textWidget->textCursor();
    QRegExp reg_exp("</p>\n<p style=\" margin");

    if (text.contains(QRegExp(reg_exp))) {
        text.replace(QRegExp(reg_exp), "</p><hr>\n<p style=\" margin");
        textWidget->setHtml(text);

        cursor.movePosition(QTextCursor::Right);
        textWidget->setTextCursor(cursor);
    }
}

// Изменение шрифта
void MainWindow::menu_button_change_font_text_clicked()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QFont font = textWidget->textCursor().charFormat().font();
    QFontDialog fontDialog(font, this);
    bool b[] = {true};
    font = fontDialog.getFont(b);

    if (b[0]) {
        saved_format = textWidget->textCursor().charFormat();
        saved_format.setFont(font);
        textWidget->textCursor().setCharFormat(saved_format);
    }
}

// Закрытие вкладки
void MainWindow::tab_close(int index)
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
    if (!file.open(QIODevice::ReadOnly)) return;

    int index = ui->text_editor_tab_widget->addTab(new QTextEdit(), file.fileName());
    ui->text_editor_tab_widget->setCurrentIndex(index);
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

    QTextStream stream(&file);

    textWidget->setReadOnly(0);
    textWidget->setPlainText( stream.read(file.size()) );
}

// Открытие файла только для чтения
void MainWindow::on_open_file_readOnly_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл только для чтения"), "./", "*.txt *.bin");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return;

    int index = ui->text_editor_tab_widget->addTab(new QTextEdit(), file.fileName());
    ui->text_editor_tab_widget->setCurrentIndex(index);
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

    QTextStream stream(&file);

    textWidget->setReadOnly(1);
    textWidget->setPlainText( stream.read(file.size()) );
}

// Сохранение в txt
void MainWindow::on_save_txt_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .txt формате"), "./", "*.txt");

    QFile file (path);
    if (!file.open(QIODevice::WriteOnly)) return;

    QTextStream stream(&file);
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    stream << textWidget->toPlainText();
    stream.flush();
}

// Сохранение в bin
void MainWindow::on_save_bin_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;
    QString author = tr("Автор: ") + ui->text_editor_author->text() + "\n\n";
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл в .bin формате"), "./", "*.bin");

    QFile file (path);
    if (!file.open(QIODevice::WriteOnly)) return;

    QTextStream stream(&file);
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    stream << author << textWidget->toPlainText();
    stream.flush();
}

// Справка
void MainWindow::on_about_triggered()
{
    QFile file (tr(":/information/text_editor_info_EN.txt"));
    if (!file.open(QIODevice::ReadOnly)) return;
    QTextStream stream(&file);
    QString message = stream.read(file.size());
    QMessageBox::information(this, tr("Информация о текстовом редакторе"), message);
}

// Перевод (false - eng)
void MainWindow::on_translate_triggered()
{
    if (translate == false)
    {
        qApp->installTranslator(&translator);
        settings->setValue("translate", false);
    }
    else
    {
        qApp->removeTranslator(&translator);
        settings->setValue("translate", true);
    }
    ui->retranslateUi(this);
    st_window->translate();
    translate = !translate;
}

// Выход
void MainWindow::on_quit_triggered()
{
    qApp->exit();
}

// Принтер
void MainWindow::on_print_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QPrinter printer;
    QPrintDialog *print_dialog = new QPrintDialog(&printer);
    print_dialog->setWindowTitle(tr("Печать"));
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());

    if (print_dialog->exec() != QDialog::Accepted) return;

    textWidget->print(&printer);
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
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    textWidget->undo();
}

// Создание таблицы
void MainWindow::add_table_function()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QTextCursor cursor = textWidget->textCursor();
    cursor.insertTable(height_new_table->get_number(),
                       width_new_table->get_number());
}

// Сохранение форматирования текста
void MainWindow::save_format_slot()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    saved_format = textWidget->textCursor().charFormat();
}

// Применение форматирования текста
void MainWindow::apply_format_slot()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    textWidget->textCursor().setCharFormat(saved_format);
}

// Выравневание текста по левому краю
void MainWindow::text_aligment_left_slot()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    textWidget->setAlignment(Qt::AlignLeft);
}

// Выравневание текста по центру
void MainWindow::text_aligment_center_slot()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    textWidget->setAlignment(Qt::AlignHCenter);
}

// Выравневание текста по правому краю
void MainWindow::text_aligment_right_slot()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;
    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    textWidget->setAlignment(Qt::AlignRight);
}

// Добавить время
void MainWindow::on_add_time_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QTextCursor cursor = textWidget->textCursor();
    cursor.insertText(QDateTime::currentDateTime().toString("hh:mm:ss"));
}

// Добавить дату
void MainWindow::on_add_date_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QTextCursor cursor = textWidget->textCursor();
    cursor.insertText(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
}

// Добавить дату и время
void MainWindow::on_add_date_and_time_triggered()
{
    if (ui->text_editor_tab_widget->currentIndex() == -1) return;

    QTextEdit *textWidget = static_cast<QTextEdit *>(ui->text_editor_tab_widget->currentWidget());
    QTextCursor cursor = textWidget->textCursor();
    cursor.insertText(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
}
