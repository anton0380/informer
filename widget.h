#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "traywidget.h"
#include "screen.h"
#include "messageframe.h"

namespace Ui {
class Widget;
}

class Widget : public TrayWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_screenshotButton_clicked();

    void on_delaySpinBox_valueChanged(int value);

    void on_alwaysCheckBox_toggled(bool checked);

private:
    Ui::Widget *ui;
    Screen *screen;
    void writeSettings();
    void readSettings();
    MessageFrame *messageFrame;
};

#endif // WIDGET_H
