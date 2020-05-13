#ifndef MENU_TABLE_LAYOUT_H
#define MENU_TABLE_LAYOUT_H

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QWidgetAction>

class menu_table_layout : public QWidgetAction
{
public:
    menu_table_layout(const QString &str);

    quint32 get_number() const;

private:
    QLabel *m_label;
    QSpinBox *m_spinbox;
};

#endif // MENU_TABLE_H
