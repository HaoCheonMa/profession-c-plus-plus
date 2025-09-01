#ifndef OPERATIONBUTTON_H
#define OPERATIONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QResizeEvent>
#include <QFont>

class OperationButton : public QPushButton
{
    Q_OBJECT
public:
    OperationButton(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);
private:
    static constexpr int baseBoxHeight = 22;
    static constexpr int baseFSize = 9;
    static QFont f;
    static int curBoxHeight;
};

#endif // OPERATIONBUTTON_H
