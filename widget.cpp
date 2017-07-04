#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    if (!server.listen(QHostAddress::Any, 6666))
    {
        close();
        return;
    }
    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->label->setText(tr("IP: %1\nport: %2\n").arg(ipAddress).arg(server.serverPort()));
}

Widget::~Widget()
{
    delete ui;
}
