#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSize>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *event) override;
signals:
    void startEvent();
    void resizing(QSize mSize);
};

#endif // MAINWINDOW_H
