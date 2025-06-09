#include "win.h"

Win::Win(QWidget *parent) noexcept : QMainWindow(parent) {
	setWindowTitle(APP_LONG_NAME);
	setFixedSize(640, 480);
    btn = new QPushButton("Hello, world!", this);
	btn->setDefault(true);
	setCentralWidget(btn);
	connect(btn, SIGNAL(clicked()), this, SLOT(close()));
}
