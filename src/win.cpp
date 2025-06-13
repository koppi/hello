#include "win.h"

#include <QHBoxLayout>
#include <qmenu.h>
#include <QMenuBar>
#include <QStatusBar>

Win::Win(QWidget *parent) noexcept : QMainWindow(parent) {
	setWindowTitle(APP_LONG_NAME);

	const auto cw = new QWidget(this);

	const auto menu = new QMenuBar(cw);
	const auto file = new QMenu(tr("&File"));
	const auto exitAct = new QAction(tr("E&xit"), this);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	file->addAction(exitAct);
	menu->addMenu(file);

	//btn = new QPushButton(tr("Hello, world!"), this);
	//btn->setDefault(true);
	//connect(btn, SIGNAL(clicked()), this, SLOT(close()));

	auto *l = new QGridLayout(cw);

	ac = new AnalogClock(this);

	// l->addWidget(btn, 0,0, Qt::AlignHCenter|Qt::AlignVCenter);
	l->addWidget(ac, 0, 0, Qt::AlignHCenter|Qt::AlignVCenter);

	setCentralWidget(cw);

	statusBar()->showMessage(tr("Ready"), 2000);
}
