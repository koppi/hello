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

    auto s1 = new QSlider(Qt::Horizontal);
    auto s2 = new QSlider(Qt::Vertical);
    auto *sb = new QSpinBox;

    auto *w = new QMainWindow;

    auto cw = new QWidget(w);

    auto menu = new QMenuBar(cw);


    auto *L = new QHBoxLayout(cw);
    L->addWidget(s1);
    L->addWidget(s2);
    L->addWidget(sb);

    QMenu *file = new QMenu("&File");
    file->addMenu("Open");
    file->addMenu("Exit");

    QMenu *Build = new QMenu("&Build");
    Build->addAction("Rebuild this file");
    Build->addAction("Rebuild All");

    menu->addMenu(file);
    menu->addMenu(Build);

    w->setCentralWidget(cw);

    w->show();

    QObject::connect  (s1,SIGNAL(valueChanged(int) ),  sb,SLOT(setValue(int) )   );
    QObject::connect  (s1,SIGNAL(valueChanged(int) ),  s2,SLOT(setValue(int) )   );

    QObject::connect  (s2,SIGNAL(valueChanged(int) ),  sb,SLOT(setValue(int) )   );
    QObject::connect  (s2,SIGNAL(valueChanged(int) ),  s1,SLOT(setValue(int) )   );

    QObject::connect  (sb,SIGNAL(valueChanged(int) ),  s1,SLOT(setValue(int) )    );
    QObject::connect  (sb,SIGNAL(valueChanged(int) ),  s2,SLOT(setValue(int) )    );

//    Win w;
//    w.show();

    return QApplication::exec();
}
