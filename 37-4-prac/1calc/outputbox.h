#ifndef OUTPUTBOX_H
#define OUTPUTBOX_H
#include <QLineEdit>
#include <QWidget>
class OutputBox : public QLineEdit
{
public:
    OutputBox(QWidget *parent);
public slots:
    void sum() {}
    void substract() {}
    void multiply() {}
    void division() {}
};

#endif // OUTPUTBOX_H
