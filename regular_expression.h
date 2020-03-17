#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H
#include <QPlainTextEdit>

class regular_expression
{
private:
    // Списки заменяемых символов
    static const QStringList list_of_reg_exp;
    static const QStringList list_of_sign;

public:
    regular_expression();

    // Функция поиска и замены символа
    static void find_and_replace(QPlainTextEdit *plain_edit);
};

#endif // REGULAR_EXPRESSION_H
