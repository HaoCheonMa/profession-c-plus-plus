#ifndef CHANNELNUMBERS_H
#define CHANNELNUMBERS_H

#pragma once
#include <QPushButton>
#include <QWidget>

class ChannelNumbers : public QPushButton
{
    Q_OBJECT
public:
    ChannelNumbers(QWidget *parent = nullptr);
};

#endif // CHANNELNUMBERS_H
