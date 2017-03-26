#include "messageframe.h"
#include "ui_messageframe.h"

// цвета
#define VFC_TABLE_NO_EDITABLE_COLOR Qt::lightGray
#define VFC_TABLE_MAX_VALUE INT_MAX

MessageFrame::MessageFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MessageFrame)
{
    ui->setupUi(this);
    messageMap.insert(QDate(2011,2,2),MessageInfo(QDate(2011,2,2),"simple message2"));
    messageMap.insert(QDate(2015,2,2),MessageInfo(QDate(2015,2,2),"simple message2"));
    messageMap.insert(QDate::currentDate(),MessageInfo(QDate::currentDate(),"simple message0"));
    messageMap.insert(QDate::currentDate(),MessageInfo(QDate::currentDate(),"событие"));
    messageMap.insert(QDate::currentDate(),MessageInfo(QDate::currentDate(),"simple message2"));
    messageMap.insert(QDate(2014,2,2),MessageInfo(QDate(2014,2,2),"simple message2"));
    showMessages();
}

MessageFrame::~MessageFrame()
{
    delete ui;
}

// заполнение ячейки таблицы данными
void MessageFrame::setTableText(int row, int col, QString str, bool editable) // throw
{
    if (!editable)
    {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(str);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        //item->setBackground(VFC_TABLE_NO_EDITABLE_COLOR);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tableWidget->setItem(row, col, item);
    }
    else
    {
        QLineEdit *edit = new QLineEdit(ui->tableWidget);
        edit->setValidator(new QIntValidator(0,VFC_TABLE_MAX_VALUE,edit));
        edit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        edit->setText(str);
        edit->setFrame(false);
        edit->setProperty("row", row);
        edit->setProperty("column", col);
        edit->setFocusPolicy(Qt::ClickFocus);
        ui->tableWidget->setCellWidget(row, col, edit);
        connect(edit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    }
}

void MessageFrame::onTextChanged(const QString & text)
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
    if (!edit)
        return;
    int row = edit->property("row").toInt();
    int col = edit->property("column").toInt();
    unsigned value = text.toUShort();
    qDebug() << "text changed" <<"row=" << row << "col=" << col << "val=" << value;
}

void MessageFrame::addRow(MessageInfo mi)
{
    //ui->tableWidget->
    int rows = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rows + 1);
    setTableText(rows, 0, mi.date.toString("dd.MM.yyyy"), false);
    setTableText(rows, 1, mi.message, false);
}

void MessageFrame::showMessages()
{
    QMultiMap<QDate, MessageInfo>::ConstIterator it = messageMap.begin();
      while( it != messageMap.end() )
      {
          addRow(it.value());
          ++it;
      }
}
