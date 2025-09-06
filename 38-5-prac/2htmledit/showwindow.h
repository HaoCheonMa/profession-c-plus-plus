#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QWidget>
#include <QWebEngineView>
#include <QtWebEngineWidgets>
#include <QUrl>
#include <QString>
#include <QDir>

class ShowWindow : public QWidget
{
    Q_OBJECT
public:
    ShowWindow(QWidget *parent = nullptr);
public slots:
    void updateHtml(QString htmlText){
        siteShow.setHtml(htmlText);
    }
private:
    QWebEngineView siteShow;
};

#endif // SHOWWINDOW_H
