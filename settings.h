#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class settings_window;
}

class settings_window : public QDialog
{
    Q_OBJECT

public:
    explicit settings_window(QWidget *parent = nullptr);
    ~settings_window();

    void translate();

private slots:
    void on_settings_accept_clicked();

    void on_settings_cancel_clicked();

    void on_settings_new_file_abort_clicked();

    void on_settings_open_file_abort_clicked();

    void on_settings_open_file_read_only_abort_clicked();

    void on_settings_save_file_to_txt_abort_clicked();

    void on_settings_save_file_to_bin_abort_clicked();

    void on_settings_quit_abort_clicked();

    void on_settings_translate_abort_clicked();

    void on_settings_settings_abort_clicked();

    void on_settings_about_abort_clicked();

private:
    Ui::settings_window *ui;
    QSettings *settings;

    void saveSettings();
    void loadSettings();
};

#endif // SETTINGS_H
