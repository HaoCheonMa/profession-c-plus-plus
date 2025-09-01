#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QWidget>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);
signals:
    void startInput();
    void onDigitPressed(int i);
private:
    int count = 0;
    static constexpr int width = 240;
    static constexpr int height = 680;
};

#endif // MAINWINDOW_H
