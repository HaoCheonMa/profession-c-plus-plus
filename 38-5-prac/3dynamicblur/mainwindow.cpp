#include "mainwindow.h"
#include "blurworker.h"

#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), sourceImage(), worker(new BlurWorker)
{
    imageLabel = new QLabel("No Image Loaded", this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(400, 300);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 10);
    slider->setValue(0);

    button = new QPushButton("Open Image", this);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(imageLabel);
    layout->addWidget(slider);
    layout->addWidget(button);
    setCentralWidget(central);
    setWindowTitle("Blur Image App");

    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::destroyed, &workerThread, &QThread::quit);
    connect(this, &MainWindow::destroyed, worker, &QObject::deleteLater);

    connect(button, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::blurRadiusChanged);

    connect(worker, &BlurWorker::resultReady, this, &MainWindow::onBlurredImageReady);

    workerThread.start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                                                    tr("Images (*.jpg *.jpeg *.png)"));
    if (!fileName.isEmpty()) {
        QImage img;
        if (img.load(fileName)) {
            sourceImage = img;
            updateImageLabel(sourceImage);
            slider->setValue(0);
        }
    }
}

void MainWindow::blurRadiusChanged(int value)
{
    if (sourceImage.isNull())
        return;

    requestBlur(value);
}

void MainWindow::requestBlur(int radius)
{
    QMetaObject::invokeMethod(worker, "process", Qt::QueuedConnection,
                              Q_ARG(QImage, sourceImage),
                              Q_ARG(int, radius));
}

void MainWindow::onBlurredImageReady(const QImage &result)
{
    if (!result.isNull()) {
        updateImageLabel(result);
    }
}

void MainWindow::updateImageLabel(const QImage &img)
{
    QImage scaled = img.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(QPixmap::fromImage(scaled));
}
