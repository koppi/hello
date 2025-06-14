#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>

#include "analogclock.h"
#include "Subscriber.h"

#include "qmqtt.h"

class Win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Win(QWidget *parent = nullptr) noexcept;

public slots:
    void aboutQt() noexcept;
    void onReceived(const QMQTT::Message& message);

private:
    QPushButton *btn;
    AnalogClock *ac;
    QLabel *label;
    Subscriber *sub;
};
