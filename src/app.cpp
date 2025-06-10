#include <QApplication>
#include<QWidget>
#include<QSlider>
#include<QSpinBox>
#include<QHBoxLayout>
#include<QMenuBar>
#include<QStatusBar>

#include "win.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win w;
    w.show();

    return QApplication::exec();
}
