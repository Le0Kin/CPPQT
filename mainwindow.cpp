#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

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
//////////////////// Задание 1 ////////////////////
void MainWindow::on_QuadEquation_button_clicked()
{
    // Переменные
    double a = ui->QuadEquation_A_num->value();
    double b = ui->QuadEquation_B_num->value();
    double c = ui->QuadEquation_C_num->value();

    // Если "а" < 0, то переменной "с" меняем знак и делим на "b".
    if (a == 0.0)
    {
        c *= -1;
        ui->QuadEquation_answer->setText(QString("x1 = %1").arg(c/b));
        return;
    }

    // Если "а" > 0, то вычисляем дискриминант, если он меньше нуля, то решений нет, если равен, то одно, иначе два решения.
    double D = pow(-b, 2) - 4 * a * c;

    if (D < 0)
    {
        ui->QuadEquation_answer->setText("Нет решения");
    }
    else if (D == 0.0)
    {
        ui->QuadEquation_answer->setText( QString("x1 = %1").arg( (-b)/(2*a) ));
    }
    else
    {
        double x1 = (-b + sqrt(D)) / (2*a);
        double x2 = (-b - sqrt(D)) / (2*a);
        ui->QuadEquation_answer->setText(QString("x1 = %1, x2 = %2").arg(x1).arg(x2));
    }
}
//////////////////// Конец задания 1 ////////////////////

//////////////////// Задание 2 ////////////////////
void MainWindow::on_SideOfATriangle_button_clicked()
{
    // Переменные
    double side_a = ui->SideOfATriangle_side_a_num->value();
    double side_b = ui->SideOfATriangle_side_b_num->value();
    double angle_c= ui->SideOfATriangle_cos_c_num->value();
    double answer;

    // Если написали градусы, то переводим в радианы
    if (!ui->SideOfATriangle_cos_c_rad->isChecked()) { angle_c = angle_c * M_PI/180; }

    // Формула
    answer = sqrt( pow(side_a, 2) + pow(side_b, 2) - (2*side_a*side_b) * (qCos(angle_c)) );

    // Ответ
    ui->SideOfATriangle_answer->setText(QString("Сторона С = %1").arg(answer));
}
//////////////////// Конец задания 2 ////////////////////

//////////////////// Задание 3 ////////////////////
void MainWindow::on_Quest3_set_default_text_clicked()
{
    // Устанавливаем текст по умолчанию
    ui->Quest3_plain_edit->setPlainText(QString("Le0Kin").arg('\n'));
}

void MainWindow::on_Quest3_set_text_of_text_line_clicked()
{
    // Добавляем строку
    ui->Quest3_plain_edit->appendPlainText( ui->Quest3_text_line->text() );
    ui->Quest3_text_line->setText("");
}

void MainWindow::on_Quest3_set_text_clicked()
{
    // Устанавливаем html разметку
    ui->Quest3_text_edit->setHtml("<font color='#a3def8'>Le0</font><font color='#e3cfdb'>Kin</font>");

}
//////////////////// Конец задания 3 ////////////////////

//////////////////// Задание 4 ////////////////////
/*
QTextDocument doc = ui->Quest3_text_edit->document();
doc.find(...);
doc.findBlock(...);
doc.setDefaultFont(...);
doc.setHtml(...);
doc.toPlainText(...);
*/
//////////////////// Конец задания 4 ////////////////////
