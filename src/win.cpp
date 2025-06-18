#include "win.h"

#include <QHBoxLayout>
#include <qmenu.h>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QFile>

#include <iostream>
#include <sstream>

Win::Win(QWidget *parent) noexcept : QMainWindow(parent) {
	setWindowTitle(APP_LONG_NAME);

	const auto cw = new QWidget(this);

	const auto menu = new QMenuBar(cw);
	const auto file = new QMenu(tr("&File"));

	const auto exitAct = new QAction(tr("E&xit"), cw);
	exitAct->setIcon(QIcon(":/icons/actions/application-exit.png"));
	exitAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
	exitAct->setToolTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	file->addAction(exitAct);
	menu->addMenu(file);

	const auto help = new QMenu(tr("&Help"), cw);
	menu->addMenu(help);

	const auto aboutQtAct = new QAction(tr("&About Qt"), cw);
	connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

	help->addAction(aboutQtAct);

	const auto tb = new QToolBar("main", cw);

	tb->addAction(exitAct);

	addToolBar(tb);

	//btn = new QPushButton(tr("Hello, world!"), this);
	//btn->setDefault(true);
	//connect(btn, SIGNAL(clicked()), this, SLOT(close()));

	auto *l = new QGridLayout(cw);

	ac = new AnalogClock(cw);
	label = new QLabel("Test", cw);

	connect(ac, &AnalogClock::valueChanged, this, &Win::updateTime);

	// l->addWidget(btn, 0,0, Qt::AlignHCenter|Qt::AlignVCenter);
	l->addWidget(ac, 0, 0, Qt::AlignHCenter|Qt::AlignVCenter);
	l->addWidget(label, 1,0, Qt::AlignHCenter|Qt::AlignVCenter);
	setCentralWidget(cw);

	statusBar()->showMessage(tr("Ready"), 2000);
}

void Win::aboutQt() noexcept
{
	QMessageBox::aboutQt(this);
}

void Win::updateTime(QTime t) {
	const QString formattedTime = t.toString("hh:mm:ss.zzz");
	label->setText(formattedTime);

	/*
	// Islamic calendar
	auto zt = date::make_zoned(date::current_zone(), std::chrono::system_clock::now());
    auto ld = date::floor<date::days>(zt.get_local_time());
    islamic::year_month_day ymd{ld};
    auto time = date::make_time(zt.get_local_time() - ld);

    std::stringstream ss;
	//ss << date::zoned_time{date::current_zone(), std::chrono::system_clock::now()};
	ss << ymd << ' ' << time << '\n';
	label->setText(QString::fromUtf8(ss.str()));
	*/
}
