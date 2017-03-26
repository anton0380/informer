#include "traywidget.h"
#include <QtWidgets>

TrayWidget::TrayWidget(QWidget *parent) : QWidget(parent)
{
    /* Инициализируем иконку трея, устанавливаем иконку из набора системных иконок,
         * а также задаем всплывающую подсказку
         * */
    trayIcon = new QSystemTrayIcon(this);  //инициализируем объект
    //trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setIcon(QIcon(":/images/icons/icon.png"));  //устанавливаем иконку
    trayIcon->setToolTip("Informer" "\n"
                             "Сохранение скриншотов");
    /* После чего создаем контекстное меню из двух пунктов*/
    QMenu * menu = new QMenu(this);
    QAction * viewWindow = new QAction(trUtf8("Развернуть окно"), this);
    QAction * quitAction = new QAction(trUtf8("Выход"), this);
    bool bOk(true);
    bOk &= (bool)connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    bOk &= (bool)connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    /* Устанавливаем контекстное меню на иконку
         * и показываем иконку приложения в трее
         * */
    trayIcon->setContextMenu(menu);
    trayIcon->show();  //отображаем объект
    /* Также подключаем сигнал нажатия на иконку к обработчику
        * данного нажатия
        * */
    bOk &= (bool) connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
               this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(bOk);
}

void TrayWidget::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->show();
//            if (!this->isVisible())
//            {  //если окно было не видимо - отображаем его
//                this->show();
//            }
//            else
//            {
//                this->hide();  //иначе скрываем
//            }
            break;
        case QSystemTrayIcon::MiddleClick:
            //QMessageBox::information(this, "TrayIcon", "Тестовое сообщение. Замените вызов этого сообщения своим кодом.");
            //showMessage();
            break;
        default:
            ;
        }
}

/* Метод, который обрабатывает событие закрытия окна приложения
 * */
void TrayWidget::closeEvent(QCloseEvent * event)
{
    /* Если окно видимо и чекбокс отмечен, то завершение приложения
     * игнорируется, а окно просто скрывается, что сопровождается
     * соответствующим всплывающим сообщением
     */
    if(this->isVisible()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

//        trayIcon->showMessage("Informer",
//                              trUtf8("Приложение свернуто в трей. Для того чтобы, "
//                                     "развернуть окно приложения, щелкните по иконке приложения в трее"),
//                              icon,
//                              2000);
    }
}
