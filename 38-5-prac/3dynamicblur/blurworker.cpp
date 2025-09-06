#include "blurworker.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>

static QImage blurImage(const QImage &source, int blurRadius)
{
    if (blurRadius == 0)
        return source;

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));
    QGraphicsBlurEffect blur;
    blur.setBlurRadius(blurRadius);
    item.setGraphicsEffect(&blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter);
    return result;
}

BlurWorker::BlurWorker(QObject *parent) : QObject(parent)
{}

void BlurWorker::process(const QImage &source, int radius)
{
    QImage result = blurImage(source, radius);
    emit resultReady(result);
}
