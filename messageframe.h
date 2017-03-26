#ifndef MESSAGEFRAME_H
#define MESSAGEFRAME_H

#include <QFrame>
#include <QtWidgets>
//#include <QMultiMap>

namespace Ui {
class MessageFrame;
}

struct MessageInfo
{
    MessageInfo(QDate date, QString message):date(date),message(message){}
    QString message;
    QDate date;

};

class MessageFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MessageFrame(QWidget *parent = 0);
    ~MessageFrame();

private:
    Ui::MessageFrame *ui;
    void addRow(MessageInfo mi);
    QMultiMap<QDate,MessageInfo> messageMap;

    void setTableText(int row, int col, QString str, bool editable);
    void onTextChanged(const QString & text);
    void showMessages();
};

#endif // MESSAGEFRAME_H
