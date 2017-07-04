#include "widget.h"
#include <QApplication>

using namespace QJson;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
