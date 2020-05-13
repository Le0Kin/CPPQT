#ifndef PUSHBUTTON_ACTIONWIDGET_H
#define PUSHBUTTON_ACTIONWIDGET_H

#include <QWidgetAction>
#include <QPushButton>

class pushButton_actionWidget : public QWidgetAction
{
public:
    pushButton_actionWidget(QPushButton *button);
};

#endif // PUSHBUTTON_ACTIONWIDGET_H
