#pragma once

#include <QMainWindow>
#include <QPushButton>

#include "clock.h"

class Win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Win(QWidget *parent = nullptr) noexcept;
private:
    QPushButton *btn;
    Clock *c;
};
