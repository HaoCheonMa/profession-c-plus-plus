#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QThread>

class QLabel;
class QSlider;
class QPushButton;
class BlurWorker;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void openImage();
    void blurRadiusChanged(int value);
    void onBlurredImageReady(const QImage &result);

private:
    void requestBlur(int radius);
    void updateImageLabel(const QImage &img);

    QLabel *imageLabel;
    QSlider *slider;
    QPushButton *button;

    QImage sourceImage;

    BlurWorker *worker;
    QThread workerThread;
};

#endif // MAINWINDOW_H
