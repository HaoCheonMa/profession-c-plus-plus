#include "channelnumbers.h"
#include <QSizePolicy>
#include <QFont>

ChannelNumbers::ChannelNumbers(QWidget *parent) : QPushButton(parent) {
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(50, 50);
    QFont f = this->font();
    f.setPointSize(20);
    this->setFont(f);

}
