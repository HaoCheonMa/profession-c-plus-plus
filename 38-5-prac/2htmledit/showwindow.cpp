#include "showwindow.h"
#include <QGridLayout>
#include <QSizePolicy>

ShowWindow::ShowWindow(QWidget *parent) :  QWidget(parent) {
    this->setStyleSheet("border-left: 5px solid gray;"
                        "border-radius: 0px;");
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(&siteShow, 0, 0);
    layout->setContentsMargins(5, 0, 0, 0);
}
