#pragma once

#include <QMainWindow>
#include <QPushButton>

class Win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Win(QWidget *parent = nullptr) noexcept;
private:
    QPushButton *btn;
};
