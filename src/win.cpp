#include "win.h"

#include <QHBoxLayout>
#include <qmenu.h>
#include <QMenuBar>
#include <QStatusBar>

Win::Win(QWidget *parent) noexcept : QMainWindow(parent) {
	auto title = QString().append(APP_LONG_NAME).append(" - rev. ").append(APP_REVISION);
	setWindowTitle(title);

	auto cw = new QWidget(this);

	auto menu = new QMenuBar(cw);
	auto file = new QMenu(tr("&File"));
	auto exitAct = new QAction(tr("E&xit"), this);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	file->addAction(exitAct);
	menu->addMenu(file);

	btn = new QPushButton(tr("Hello, world!"), this);
	btn->setDefault(true);

	connect(btn, SIGNAL(clicked()), this, SLOT(close()));

	auto *l = new QGridLayout(cw);
	l->addWidget(btn, 0,0, Qt::AlignHCenter|Qt::AlignVCenter);

	setCentralWidget(cw);

	statusBar()->showMessage(tr("Ready"), 2000);
}
