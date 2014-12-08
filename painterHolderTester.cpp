#include "painterholder.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PainterHolder p;
    p.show();

    return a.exec();
}
