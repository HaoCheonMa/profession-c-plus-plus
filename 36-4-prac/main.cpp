#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        mGreenCircle.load("D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/36-4-prac/assets/Green.png");
        mYellowCircle.load("D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/36-4-prac/assets/Yellow.png");
        mRedCircle.load("D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/36-4-prac/assets/Red.png");
        mCurrentCircle = mGreenCircle;
    }

    QSize minimumSizeHint() const override { return QSize(300, 300); }

    void setGreen()    { mCurrentCircle = mGreenCircle; update(); }
    void setYellow()   { mCurrentCircle = mYellowCircle; update(); }
    void setRed()      { mCurrentCircle = mRedCircle; update(); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        if (!mCurrentCircle.isNull()) {
            QPixmap scaled = mCurrentCircle.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QPoint center = rect().center() - QPoint(scaled.width() / 2, scaled.height() / 2);
            painter.drawPixmap(center, scaled);
        }
    }

private:
    QPixmap mGreenCircle;
    QPixmap mYellowCircle;
    QPixmap mRedCircle;
    QPixmap mCurrentCircle;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(500, 500);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    Circle *circle = new Circle(&window);
    QSlider *slider = new QSlider(Qt::Horizontal, &window);
    slider->setRange(0, 99);
    slider->setValue(0);

    layout->addWidget(circle);
    layout->addWidget(slider);

    layout->setAlignment(circle, Qt::AlignCenter);

    QObject::connect(slider, &QSlider::valueChanged, [circle](int value){
        if (value < 33)
            circle->setGreen();
        else if (value < 66)
            circle->setYellow();
        else
            circle->setRed();
    });

    window.setWindowTitle("Colorful Circle");
    window.show();

    return app.exec();
}

#include "main.moc"
