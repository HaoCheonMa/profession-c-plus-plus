#include "editwindow.h"
#include <QGridLayout>
#include <QSizePolicy>
#include <QFile>
#include <QTextStream>

void EditWindow::setBaseText(const QString &filePath) {

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл" << filePath;
        return;
    }
    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();
    codeEdit.setPlainText(htmlContent);
    return;
}

EditWindow::EditWindow(QWidget *parent) : QWidget(parent) {
    this->setObjectName("mPlain");
    this->setStyleSheet("#mPlain {border-right: 5px solid gray;"
                        "border-radius: 0px;}");

    codeEdit.setObjectName("codeEdit");
    codeEdit.setStyleSheet("#codeEdit {background-color: white;"
                           "color: black;"
                           "font-size: 14pt;}");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(&codeEdit, 0, 0);
    layout->setContentsMargins(0, 0, 5, 0);

    connect(&codeEdit, &QPlainTextEdit::textChanged, this, &EditWindow::onTextChanged);
    EditWindow::setBaseText("../../baseHtml.html");
}

QString EditWindow::getCodeEditText() const {
    return codeEdit.toPlainText();
}

