#ifndef SCREENDATA_H
#define SCREENDATA_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QTimer>

class ScreenData : public QLabel
{
    Q_OBJECT
public:
    ScreenData(QString _text, QWidget *parent = nullptr);
    QString getText(){return withValue;}
public slots:
    void upValue(){
        if (textChannel == "V O L U M E\n↓\n")
            value += 10;
        else
            ++value;

        normalizeButtons();
        updateValue();
    }
    void lowValue(){
        if (textChannel == "V O L U M E\n↓\n")
            value -= 10;
        else
            --value;

        normalizeButtons();
        updateValue();
    }

    // Ввод цифры
    void inputValues(int i) {
        if (!inputTimer.isActive()) {
            value = 0;
            withValue = textChannel;
            setText(withValue);
        }

        QString baseText = textChannel;
        QString currentText = text().startsWith(baseText) ? text().mid(baseText.length()) : text();
        currentText += QString::number(i);

        withValue = baseText + currentText;
        setText(withValue);

        bool ok;
        int newValue = currentText.toInt(&ok);
        if (ok) {
            value = newValue;
        }

        normalizeValue();

        inputTimer.start();

        qDebug() << "Input Values:" << value << withValue;
    }

    void onInputTimeout() {
        qDebug() << "Input complete, final value:" << value;
        updateValue();
    }
private:
    int channelsAmount = 100;
    short value = 0;
    QString textChannel;
    QString withValue;
    QTimer inputTimer;
    //"C H A N N E L\n↓\n" + QString::number(value);
    //"V O L U M E\n↓\n" + QString::number(value);

    void normalizeValue() {
        if (textChannel == "V O L U M E\n↓\n") {
            if (value < 0)
                value = 0;
            if (value > 100)
                value = 100;
        } else
            if (value > channelsAmount)
                value = channelsAmount;
    }

    void updateValue(){
        withValue = textChannel + QString::number(value);
        this->setText(withValue);
    }

    void normalizeButtons(){
        if (textChannel == "V O L U M E\n↓\n") {
            if (value < 0)
                value = 0;
            if (value > 100)
                value = 100;
        } else {
            if (value > channelsAmount)
                value = 0;
            if (value < 0)
                value = channelsAmount;
        }
    }
};

#endif // SCREENDATA_H
