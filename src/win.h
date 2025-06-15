#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QTime>

#include "analogclock.h"

class Win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Win(QWidget *parent = nullptr) noexcept;

public slots:
    void aboutQt() noexcept;
	void updateTime(QTime t);

private:
    QPushButton *btn;
    AnalogClock *ac;
    QLabel *label;
};
