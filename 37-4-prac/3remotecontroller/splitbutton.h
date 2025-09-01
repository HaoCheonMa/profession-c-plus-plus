#ifndef SPLITBUTTON_H
#define SPLITBUTTON_H

#pragma once

#include <QPushButton>
#include <QMouseEvent>

class SplitButton : public QPushButton
{
    Q_OBJECT
public:
    SplitButton(QWidget *parent = nullptr);
signals:
    void upperClicked();
    void lowerClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
};

#endif // SPLITBUTTON_H
