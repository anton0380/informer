#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>
#include <QtWidgets>

class Screen : public QObject
{
    Q_OBJECT
public:
    explicit Screen(QObject *parent = 0);
    //  сделать скриншот
    void screenshot();
    // путь сохранения скриншотов
    void setDir(QString dir) {this->dir = dir;}
    QString getDir() {return dir;}
    // сохранять по таймеру
    void setAlways(bool always);
    bool getAlways() {return always;}
    // задержка таймера (секунд)
    void setDelay(int delay);
    int getDelay() {return delay;}


signals:

public slots:
    void timeout();

private:
    QString dir;
    QTimer *timer;
    bool always;
    int delay;
};

#endif // SCREEN_H
