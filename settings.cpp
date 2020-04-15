#include "settings.h"
#include "ui_settings.h"

settings_window::settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings_window)
{
    ui->setupUi(this);

    settings = new QSettings();
    loadSettings();
}

settings_window::~settings_window()
{
    delete ui;
}

void settings_window::translate()
{
    ui->retranslateUi(this);
}

void settings_window::saveSettings()
{
    settings->setValue("new_file_key_hotkey",               ui->settings_new_file_key->keySequence());
    settings->setValue("open_file_key_hotkey",              ui->settings_open_file_key->keySequence());
    settings->setValue("open_file_read_only_key_hotkey",    ui->settings_open_file_read_only_key->keySequence());
    settings->setValue("save_file_txt_key_hotkey",          ui->settings_save_file_to_txt_key->keySequence());
    settings->setValue("save_file_bin_key_hotkey",          ui->settings_save_file_to_bin_key->keySequence());
    settings->setValue("print_file_hotkey",                 ui->settings_print_file_key->keySequence());
    settings->setValue("quit_key_hotkey",                   ui->settings_quit_key->keySequence());
    settings->setValue("translate_key_hotkey",              ui->settings_translate_key->keySequence());
    settings->setValue("settings_key_hotkey",               ui->settings_settings_key->keySequence());
    settings->setValue("about_key_hotkey",                  ui->settings_about_key->keySequence());
    settings->setValue("styleSheet_index",                  ui->settings_styleSheet_box->currentIndex());
}

void settings_window::loadSettings()
{
    ui->settings_new_file_key->setKeySequence(              settings->value("new_file_key_hotkey", "Ctrl+N").toString());
    ui->settings_open_file_key->setKeySequence(             settings->value("open_file_key_hotkey", "Ctrl+O").toString());
    ui->settings_open_file_read_only_key->setKeySequence(   settings->value("open_file_read_only_key_hotkey", "Ctrl+R").toString());
    ui->settings_save_file_to_txt_key->setKeySequence(      settings->value("save_file_txt_key_hotkey", "Ctrl+S").toString());
    ui->settings_save_file_to_bin_key->setKeySequence(      settings->value("save_file_bin_key_hotkey").toString());
    ui->settings_print_file_key->setKeySequence(            settings->value("print_file_hotkey", "Ctrl+P").toString());
    ui->settings_quit_key->setKeySequence(                  settings->value("quit_key_hotkey", "Ctrl+Q").toString());
    ui->settings_translate_key->setKeySequence(             settings->value("translate_key_hotkey", "Ctrl+T").toString());
    ui->settings_settings_key->setKeySequence(              settings->value("settings_key_hotkey").toString());
    ui->settings_about_key->setKeySequence(                 settings->value("about_key_hotkey").toString());
    ui->settings_styleSheet_box->setCurrentIndex(           settings->value("styleSheet_index", 0).toInt());
}

void settings_window::on_settings_accept_clicked()
{
    saveSettings();
    this->close();
}

void settings_window::on_settings_cancel_clicked()
{
    this->close();
}

void settings_window::on_settings_new_file_abort_clicked()
{
    ui->settings_new_file_key->setKeySequence(QString("Ctrl+N"));
}

void settings_window::on_settings_open_file_abort_clicked()
{
    ui->settings_open_file_key->setKeySequence(QString("Ctrl+O"));
}

void settings_window::on_settings_open_file_read_only_abort_clicked()
{
    ui->settings_open_file_read_only_key->setKeySequence(QString("Ctrl+R"));
}

void settings_window::on_settings_save_file_to_txt_abort_clicked()
{
    ui->settings_save_file_to_txt_key->setKeySequence(QString("Ctrl+S"));
}

void settings_window::on_settings_save_file_to_bin_abort_clicked()
{
    ui->settings_save_file_to_bin_key->setKeySequence(QString(""));
}

void settings_window::on_settings_print_file_abort_clicked()
{
    ui->settings_print_file_key->setKeySequence(QString("Ctrl+P"));
}

void settings_window::on_settings_quit_abort_clicked()
{
    ui->settings_quit_key->setKeySequence(QString("Ctrl+Q"));
}

void settings_window::on_settings_translate_abort_clicked()
{
    ui->settings_translate_key->setKeySequence(QString("Ctrl+T"));
}

void settings_window::on_settings_settings_abort_clicked()
{
    ui->settings_settings_key->setKeySequence(QString(""));
}


void settings_window::on_settings_about_abort_clicked()
{
    ui->settings_about_key->setKeySequence(QString(""));
}
