#include "mainwindow.h"
#include "channelnumbers.h"
#include "splitbutton.h"
#include "screendata.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    setFixedSize(width, height);

    //Кнопки/сетка
    std::vector<ChannelNumbers*> nums;
    nums.reserve(10);
    for(int i = 0; i < 10; ++i){
        nums.push_back(new ChannelNumbers());
        nums[i]->setText(QString::number(i));
    }
    QGridLayout *channelNumbers = new QGridLayout();
    channelNumbers->setContentsMargins(0, 0, 0, 20);
    channelNumbers->setSpacing((this->width-nums[1]->width() * 3) / 4);

    //Создание кнопок
    {
        int row = 0;
        int column = 0;
        int id = 0;
        for(int i = 1 ; i < 10; ++i){
            channelNumbers->addWidget(nums[i], row, column);
            if (i % 3 == 0) ++row;
            column == 2 ? column = 0 : ++column;
        }
        channelNumbers->addWidget(nums[0], 3, 1);
    }

    //Кнопки каналы/звук
    QGridLayout *funBtns = new QGridLayout();
    SplitButton *changeChannel = new SplitButton();
    SplitButton *changeVolume = new SplitButton();
    funBtns->setHorizontalSpacing(90);
    funBtns->setContentsMargins(0, 0, 0, 20);
    funBtns->addWidget(changeChannel, 0, 0, 1, 1);
    funBtns->addWidget(changeVolume, 0, 2, 1, 1);
    changeChannel->setText("↑\nCH\n↓");
    changeVolume->setText("↑\nVO\n↓");

    //Экранчик
    QWidget *screen = new QWidget();
    QVBoxLayout *screenDataLayout = new QVBoxLayout(screen);
    QString textChannel = "C H A N N E L\n↓\n";
    QString textVolume = "V O L U M E\n↓\n";
    ScreenData *channel = new ScreenData(textChannel);
    ScreenData *volume = new ScreenData(textVolume);
    screen->setFixedSize(200, 250);
    screen->setObjectName("screen");
    screen->setStyleSheet("QWidget#screen { border: 2px solid orange; background-color: dark-gray}");
    screenDataLayout->addWidget(channel);
    screenDataLayout->addWidget(volume);
    screenDataLayout->setAlignment(Qt::AlignCenter);
    screenDataLayout->setSpacing(15);
    channel->setText(channel->getText());
    volume->setText(volume->getText());

    //Сигналы
    connect(changeChannel, &SplitButton::upperClicked, channel, &ScreenData::upValue);
    connect(changeChannel, &SplitButton::lowerClicked, channel, &ScreenData::lowValue);
    connect(changeVolume, &SplitButton::upperClicked, volume, &ScreenData::upValue);
    connect(changeVolume, &SplitButton::lowerClicked, volume, &ScreenData::lowValue);
    for(int i = 0; i < 10; ++i){
        connect(nums[i], &ChannelNumbers::clicked, this, [this, i]() mutable{
            emit onDigitPressed(i);
        });
    }
    connect(this, &MainWindow::onDigitPressed, channel, &ScreenData::inputValues);

    //Главная сетка
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(channelNumbers);
    mainLayout->addLayout(funBtns);
    mainLayout->addWidget(screen);
}


