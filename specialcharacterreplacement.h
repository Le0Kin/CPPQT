#ifndef SPECIALCHARACTERREPLACEMENT_H
#define SPECIALCHARACTERREPLACEMENT_H
#include <QtCore>
#include <QRegularExpression>


class SpecialCharacterReplacement
{
private:
    static QRegExp m_copy_right;
    static QRegExp m_ppm;
    static QRegExp m_trademark;
    static QRegExp m_euro;
    static QRegExp m_ruble;
public:
    SpecialCharacterReplacement();
    void static find_replace(QString text);
};

#endif // SPECIALCHARACTERREPLACEMENT_H
