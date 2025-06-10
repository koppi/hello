#include "win.h"

#include <QHBoxLayout>
#include <qmenu.h>
#include <QMenuBar>
#include <QStatusBar>

Win::Win(QWidget *parent) noexcept : QMainWindow(parent) {
	setWindowTitle(APP_LONG_NAME);

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

	auto *l = new QHBoxLayout(cw);
	l->addWidget(btn);

	setCentralWidget(cw);

	statusBar()->showMessage(tr("Ready"), 2000);
}
