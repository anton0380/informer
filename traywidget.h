#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

class TrayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrayWidget(QWidget *parent = 0);

protected:
    /* Виртуальная функция родительского класса в нашем классе
     * переопределяется для изменения поведения приложения,
     *  чтобы оно сворачивалось в трей, когда мы этого хотим
     */
    void closeEvent(QCloseEvent * event);

signals:

public slots:

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

private:
    QSystemTrayIcon *trayIcon;
};

#endif // TRAYWIDGET_H
