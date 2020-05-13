#include "menu_table_layout.h"

menu_table_layout::menu_table_layout(const QString &str) :
    QWidgetAction(NULL)
{
    QHBoxLayout *layout = new QHBoxLayout();
    m_label = new QLabel(str);
    m_spinbox = new QSpinBox();
    m_spinbox->setMinimum(1);

    layout->addWidget(m_label);
    layout->addWidget(m_spinbox);

    QWidget *widget = new QWidget(NULL);
    widget->setLayout(layout);

    setDefaultWidget(widget);
}

quint32 menu_table_layout::get_number() const
{
    return m_spinbox->value();
}
