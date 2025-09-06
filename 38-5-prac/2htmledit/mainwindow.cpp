#include "mainwindow.h"
#include "editwindow.h"
#include "showwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->resize(mWidth, mHeight);
    this->setMinimumSize(700, 500);
    EditWindow *wEdit = new EditWindow();
    ShowWindow *wShow = new ShowWindow();
    QHBoxLayout *mLayout = new QHBoxLayout(this);
    mLayout->setSpacing(0);
    // mLayout->setContentsMargins(0, 0, 0, 0);
    mLayout->addWidget(wEdit, 1);
    mLayout->addWidget(wShow, 1);
    connect(wEdit, &EditWindow::updateText, wShow, &ShowWindow::updateHtml);
    wShow->updateHtml(wEdit->getCodeEditText());
}
