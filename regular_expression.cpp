#include "regular_expression.h"

regular_expression::regular_expression(){}

// Списки заменяемых символов
const QStringList regular_expression::list_of_reg_exp = {"COPYRIGHT", "PPM", "TRADEMARK", "EURO", "RUBLE"};
const QStringList regular_expression::list_of_sign    = {"©"        , "‰"  , "®"        , "€"   , "₽"};

// Функция поиска и замены символа
void regular_expression::find_and_replace(QPlainTextEdit *plain_edit)
{
    // Переменные
    QString text = plain_edit->toPlainText();
    QRegExp reg_exp;

    // Переменная для установки каретки в нужное место после замены символа
    QTextCursor cursor;


    // Если найдено регулярное выражение, то заменить его
    for (int i = 0; i < list_of_reg_exp.length(); i++)
    {
        reg_exp.setPattern( list_of_reg_exp.at(i) );
        if (text.contains(reg_exp))
        {
            // Запоминаем где находился курсор до замены символа и передвигаем его на следующий символ
            cursor = plain_edit->textCursor();
            cursor.movePosition(QTextCursor::Right);

            // Заменяем текст на символ и переносим каретку в нужное место
            plain_edit->setPlainText( text.replace(reg_exp, list_of_sign.at(i)) );
            plain_edit->setTextCursor(cursor);
        }
    }
}
