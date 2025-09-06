#ifndef REDBUTTON_H
#define REDBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QPaintEvent>
#include <QWidget>
#include <QSize>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class RedButton : public QPushButton
{
    Q_OBJECT
public:
    RedButton(QWidget *parent = nullptr);
public slots:
    void keepSize(QSize btnSize) {
        normalBtn = originalNormal.scaled(btnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pressedBtn = originalPressed.scaled(btnSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    void setPressedNormal(){
        sndPlayer.play();
        curBtn = pressedBtn;
        update();
        timer.start(100);
    }
private slots:
    void onTimeout(){
        curBtn = normalBtn;
        update();
    }
private:
    QTimer timer;
    QPixmap originalNormal;
    QPixmap originalPressed;
    QPixmap normalBtn;
    QPixmap pressedBtn;
    QPixmap curBtn;
    QUrl sndSource = QUrl::fromLocalFile("assets/click.mp3");
    QMediaPlayer sndPlayer;
    QAudioOutput sndOutput;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // REDBUTTON_H
