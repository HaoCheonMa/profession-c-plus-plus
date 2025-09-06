#ifndef BLURWORKER_H
#define BLURWORKER_H

#include <QObject>
#include <QImage>

class BlurWorker : public QObject {
    Q_OBJECT
public:
    explicit BlurWorker(QObject *parent = nullptr);

public slots:
    void process(const QImage &source, int radius);

signals:
    void resultReady(const QImage &result);
};

#endif // BLURWORKER_H
