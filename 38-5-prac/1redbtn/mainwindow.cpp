#include "mainwindow.h"
#include "redbutton.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(200, 200);
    RedButton *btn = new RedButton(nullptr);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(btn);
    this->setLayout(layout);
    connect(this, &MainWindow::resizing, btn, &RedButton::keepSize);
    connect(btn, &RedButton::clicked, btn, &RedButton::setPressedNormal);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QSize newSize = event->size();

    int btnWidth = newSize.width() * 0.75;
    int btnHeight = btnWidth;
    QSize btnSize(btnWidth, btnHeight);

    emit resizing(btnSize);
}
