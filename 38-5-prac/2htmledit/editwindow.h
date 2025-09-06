#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QString>

class EditWindow : public QWidget
{
    Q_OBJECT
public slots:
    void onTextChanged(){
        emit updateText(codeEdit.toPlainText());
    };
signals:
    void updateText(QString htmlText);
public:
    EditWindow(QWidget *parent = nullptr);
    void setBaseText(const QString &filepath);
    QString getCodeEditText() const;
private:
    QPlainTextEdit codeEdit;
};

#endif // EDITWINDOW_H
