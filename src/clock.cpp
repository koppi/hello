#include "clock.h"

Clock::Clock(int w, int h, QWidget *parent) : WIDTH(w), HEIGHT(h), H_WIDTH(WIDTH/2), H_HEIGHT(HEIGHT/2), RADIUS(H_HEIGHT - 50), QWidget(parent) {
    resize(w, h);

    m_radiusMap["sec"]   = RADIUS - 10;
    m_radiusMap["min"]   = RADIUS - 55;
    m_radiusMap["hour"]  = RADIUS - 100;
    m_radiusMap["digit"] = RADIUS - 30;
    for(int i = 0; i < 60; ++i)
    {
        m_clock60[i] = i*6;
    }

    QObject::connect(&m_timer, &QTimer::timeout, this, &Clock::animationLoop);

    m_timer.start(static_cast<int>(1000.f / 60.f)); // 60 times per second

    m_elapsedTimer.start();
}
