#include "widget.h"
#include <QApplication>

int argument_count;
char ** argument;

int main(int argc, char *argv[])
{
    argument_count=argc;
    argument = argv;
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
