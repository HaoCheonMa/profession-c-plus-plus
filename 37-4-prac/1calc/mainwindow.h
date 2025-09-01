#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QString>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    enum class Operation {
        Sum,
        Subtract,
        Multiply,
        Divide
    };
    Q_ENUM(Operation)

signals:
    void calculate(const QString&, const QString&, Operation);
};

#endif // MAINWINDOW_H
