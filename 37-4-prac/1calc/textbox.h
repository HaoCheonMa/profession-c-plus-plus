#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QResizeEvent>
#include <QString>
#include "mainwindow.h"

class TextBox : public QLineEdit
{
    Q_OBJECT
public:
    TextBox(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void calculate(const QString &firstNum, const QString &secondNum, MainWindow::Operation op);
private:
    static constexpr int baseBoxHeight = 22;
    static constexpr int baseFSize = 9;
    static int curBoxHeight;
    static QFont f;
};

#endif // TEXTBOX_H
