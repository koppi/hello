#include <QtWidgets/QApplication>

#include "win.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win w; w.resize(500,500); w.show();

    return QApplication::exec();
}
