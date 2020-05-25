#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString host = ui->IPAdress_lineEdit->text();
    quint16 port = ui->port_lineEdit->text().toUInt();

    QLineEdit* name = ui->name_lineEdit;
    QPlainTextEdit* description = ui->description_plainTextEdit;
    QLineEdit* dateStart = ui->datestart_lineEdit;
    QLineEdit* dateEnd = ui->dateend_lineEdit;
    QLineEdit* progress = ui->progress_lineEdit;

    QString command = "INSERT INTO tasks (name, description, datestart, dateend, progress)"
                      "VALUES ( '" + name->text() + "', '" + description->toPlainText() + "', '" + dateStart->text() + "', '" + dateEnd->text() + "', '" + progress->text() + "' )";

    socket->connectToHost(host, port);
    socket->write(command.toUtf8());

    socket->disconnectFromHost();
    name->clear();
    description->clear();
    dateStart->clear();
    dateEnd->clear();
    progress->clear();
}
