#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private:
    const int mWidth = 1536;
    const int mHeight = 836;
};

#endif // MAINWINDOW_H
