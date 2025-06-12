#include <QtWidgets/QApplication>

#include "win.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win w; w.show();

    return QApplication::exec();
}
