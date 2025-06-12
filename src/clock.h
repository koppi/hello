#pragma once

// https://github.com/Przemekkkth/AnalogClock_Qt-Cpp

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QPoint>
#include <QPainter>
#include <QObject>
#include <QTime>
#include <cmath>

static double DEG_TO_RAD(double degrees)
{
    return degrees * (M_PI / 180);
}

class Clock : public QWidget {
Q_OBJECT

public:
    explicit Clock(int w, int h, QWidget *parent = nullptr);
    ~Clock() override { }

private:
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    const int WIDTH;
    const int HEIGHT;
    const int H_WIDTH;
    const int H_HEIGHT;
    const int RADIUS;
    QMap<QString, int> m_radiusMap;
    QMap<int, int> m_clock60;
    int m_hour, m_minute, m_second;

private slots:
    void animationLoop() {
        update();
    }

private:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter qp(this);
        qp.setBrush(QBrush(Qt::black));
        qp.drawRect(0,0,size().width(), size().height());
        drawFace(qp);
        drawClock(qp);
        drawText(qp);
    }
    QPointF getClockPos(int clock_hand, QString key) {
        double x = H_WIDTH + m_radiusMap[key] * std::cos(DEG_TO_RAD(m_clock60[clock_hand]) - M_PI_2);
        double y = H_HEIGHT + m_radiusMap[key] * std::sin(DEG_TO_RAD(m_clock60[clock_hand]) - M_PI_2);
        return QPointF(x, y);
    }
    void drawFace(QPainter& p){
        p.save();
        for(auto map_element = m_clock60.begin(); map_element != m_clock60.end(); ++map_element)
        {
            int digit = map_element.key();
            int radius = 0;
            if (digit % 3 == 0 && digit % 5 == 0) {
                radius = 5;
            } else if (digit % 5 == 0) {
                radius = 2;
            } else {
                radius = 1;
            }
            p.setRenderHint(QPainter::Antialiasing);
            p.setBrush(QBrush(Qt::transparent));
            p.setPen(QPen(Qt::white, 7.0f));
            if(radius == 1)
            {
                p.setBrush(QBrush(Qt::white));
            }
            p.drawEllipse(getClockPos(digit, "digit"), radius, radius);
        }
        p.restore();
    }
    void drawClock(QPainter& p)
    {
        p.save();
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::red, 10.0f));
        p.setBrush(QBrush(Qt::red));
        p.drawLine(QPointF(H_WIDTH, H_HEIGHT), getClockPos(m_hour, "hour") );

        p.setPen(QPen(Qt::green, 7.0f));
        p.setBrush(QBrush(Qt::green));
        p.drawLine(QPointF(H_WIDTH, H_HEIGHT), getClockPos(m_minute, "min") );

        p.setPen(QPen(Qt::blue, 4.0f));
        p.setBrush(QBrush(Qt::blue));
        p.drawLine(QPointF(H_WIDTH, H_HEIGHT), getClockPos(m_second, "sec") );

        p.setPen(QPen(Qt::white));
        p.setBrush(QBrush(Qt::white));
        p.drawEllipse(QPointF(H_WIDTH, H_HEIGHT), 8.0f, 8.0f);
        p.restore();
    }
    void drawText(QPainter& p)
    {
        p.save();
        p.setFont(QFont());
        p.setBrush(QBrush(Qt::red));
        p.setPen(Qt::white);
        QFont font = p.font();
        font.setPointSize(font.pointSize()*2.5);
        p.setFont(font);
        p.drawText(QPointF(0,font.pointSize()),getCurrentTime()) ;
        p.restore();
    }
    QString getCurrentTime()
    {
        QTime t = QTime::currentTime();
        QString retVal = t.toString("hh:mm:ss");
        m_hour = ( (t.hour()%12)*5 + t.minute() / 12 ) % 60;
        m_minute = t.minute();
        m_second = t.second();

        return retVal;
    }
};
