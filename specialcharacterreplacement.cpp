#include "specialcharacterreplacement.h"
#include <iostream>

SpecialCharacterReplacement::SpecialCharacterReplacement() {}

QRegExp SpecialCharacterReplacement::m_copy_right("*C*");
QRegExp SpecialCharacterReplacement::m_ppm("%О");
QRegExp SpecialCharacterReplacement::m_trademark("*Р*");
QRegExp SpecialCharacterReplacement::m_euro("Е-");
QRegExp SpecialCharacterReplacement::m_ruble("Р-");

void SpecialCharacterReplacement::find_replace(QString text)
{
    quint32 begin = -1;
    quint32 length = -1;



    text.replace(begin, length, "©");
}
