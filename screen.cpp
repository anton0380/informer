#include "screen.h"
#include <QDebug>
#include <QtWidgets>

Screen::Screen(QObject *parent) : QObject(parent)
{
    dir = QApplication::applicationDirPath();
    always = false;
    delay = 6;
    timer = new QTimer(this);
    bool bOk(true);
    bOk &= (bool)connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    Q_ASSERT(bOk);
}

// делаем скриншот экрана
void Screen::screenshot()
{
    QDateTime dateTime = QDateTime::currentDateTime();

    QString fileDir = dir + dateTime.toString("/yyyy_MM_dd");
    QString fileName = fileDir + dateTime.toString("/hh_mm_ss.png");
    qDebug() << fileName;
    QDir().mkpath(fileDir);
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        QPixmap pixmap = screen->grabWindow(0);//((WId) FindWindow(NULL, L"Blacklight Retribution"));
        pixmap.save(fileName);
    }

//    QScreen * screen = QGuiApplication::primaryScreen();
//    QRect g = screen->geometry();
//    QPixmap pixmap = screen->grabWindow(0, g.x(), g.y(), g.width(), g.height());
//    pixmap.save(name, "JPG", screenshot_quality);



    //QPixmap pixmap = QPixmap::grabWindow ( QApplication::desktop()->winId(), x, y, width, height) ;
    //QApplication::desktop()->raise();
//    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    //pixmap.save(fileName, "PNG", 0);
//    pixmap.save(fileName);
}

// таймер записи скриншотов
void Screen::timeout()
{
    if (always)
        screenshot();
}

void Screen::setAlways(bool always)
{
    if (this->always != always)
    {
        this->always = always;
        if (always)
            timer->start(delay * 1000);
        else
            timer->stop();
    }
}

void Screen::setDelay(int delay)
{
    this->delay = delay;
    if (always)
    {
        timer->start(delay * 1000);
    }
}
