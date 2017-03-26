#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    TrayWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    messageFrame = new MessageFrame();
    ui->messageLayout->addWidget(messageFrame);
    messageFrame->show();
    screen = new Screen(this);
    readSettings();
}

Widget::~Widget()
{
    writeSettings();
    delete ui;
}


void Widget::on_screenshotButton_clicked()
{
    screen->screenshot();
}

void Widget::on_delaySpinBox_valueChanged(int value)
{
    screen->setDelay(value);
    qDebug() << value;
}

// загрузка настроек
void Widget::writeSettings()
 {
     QSettings settings("informer.ini", QSettings::IniFormat);
     settings.beginGroup("Window");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
     settings.endGroup();
     settings.beginGroup("Screen");
     settings.setValue("always", screen->getAlways());
     settings.setValue("delay", screen->getDelay());
     settings.endGroup();
 }

// сохранение настроек
 void Widget::readSettings()
 {
     QSettings settings("informer.ini", QSettings::IniFormat);
     settings.beginGroup("Window");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
     settings.endGroup();
     settings.beginGroup("Screen");
     bool always = settings.value("always", screen->getAlways()).toBool();
     int delay = screen->getDelay();
     ui->alwaysCheckBox->setChecked(settings.value("always", screen->getAlways()).toBool());
     ui->delaySpinBox->setValue(settings.value("delay", screen->getDelay()).toInt());
     settings.endGroup();
 }

void Widget::on_alwaysCheckBox_toggled(bool checked)
{
    screen->setAlways(checked);
}
