#include "pushbutton_actionwidget.h"

pushButton_actionWidget::pushButton_actionWidget(QPushButton *button) :
    QWidgetAction(NULL)
{
    setDefaultWidget(button);
}
