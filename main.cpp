#include "widget.h"
#include <QApplication>

void dummyOutput(QtMsgType, const QMessageLogContext&, const QString&)
{

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef QT_DEBUG
    qInstallMessageHandler(dummyOutput);
#endif
    Widget w;
    w.show();
    return a.exec();
}
