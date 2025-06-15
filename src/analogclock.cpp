/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "analogclock.h"

#include <QPainter>
#include <QTimer>
#include <QStyle>
#include <QApplication>

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent) {
    QTimer *timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);

    connect(timer, &QTimer::timeout, this,
            QOverload<>::of(&AnalogClock::timerTimeout));

    timer->start(60.f / 1000.f);
}

void AnalogClock::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const int side = qMin(width(), height());

    //painter.setBrush(QBrush(Qt::black));
    //painter.drawRect(0,0,size().width(), size().height());

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    paintDefault(&painter);
}

void AnalogClock::timerTimeout() {
	m_time = QTime::currentTime();
	
	emit valueChanged(m_time);
    update();
}

void AnalogClock::paintDefault(QPainter *painter) {
    static const QPolygon hourHand({
        QPoint(5, 14),
        QPoint(-5, 14),
        QPoint(-4, -71),
        QPoint(4, -71)
    });
    static const QPolygon minuteHand({
        QPoint(4, 14),
        QPoint(-4, 14),
        QPoint(-3, -89),
        QPoint(3, -89)
    });
    static const QPolygon secondsHand(QVector<QPoint>({
        QPoint(1, 14),
        QPoint(-1, 14),
        QPoint(-1, -89),
        QPoint(1, -89)
    }));

    static const QLine hourMarker(88, 0, 96, 0);
    static const QLine minuteMarker(92, 0, 96, 0);

    const QColor hourColor(Qt::red);
    const QColor minuteColor(Qt::green);

    paintHourHand(painter, hourHand, hourColor);
    paintHourMarkers(painter, hourMarker, Qt::black);

    paintMinuteHand(painter, minuteHand, minuteColor);
    paintMinuteMarkers(painter, minuteMarker, Qt::black);

	paintSecondsHand(painter, secondsHand, Qt::blue);
}

void AnalogClock::paintImg(QPainter *painter, const QString &imgpath) {
    painter->drawPixmap(-100, -100, 200, 200, QPixmap(imgpath));
}

void AnalogClock::paintHourHand(QPainter *painter, const QPolygon &poly,
                                const QColor &color) {
    painter->setBrush(color);

    painter->save();
    painter->rotate(30.0 * ((m_time.hour() + m_time.minute() / 60.0)));
    painter->drawConvexPolygon(poly);
    painter->restore();

    painter->setPen(Qt::NoPen);
}

void AnalogClock::paintHourMarkers(QPainter *painter, const QLine &line,
                                   const QColor &color) {
    painter->setPen(color);
    for (int i = 0; i < 12; ++i) {
        painter->drawLine(line);
        painter->rotate(30.0);
    }

    painter->setPen(Qt::NoPen);
}

void AnalogClock::paintMinuteHand(QPainter *painter, const QPolygon &poly,
                                  const QColor &color) {
    painter->setBrush(color);

    painter->save();
    painter->rotate(6.0 * (m_time.minute() + m_time.second() / 60.0));
    painter->drawConvexPolygon(poly);
    painter->restore();

    painter->setPen(Qt::NoPen);
}
void AnalogClock::paintMinuteMarkers(QPainter *painter, const QLine &line,
                                     const QColor &color) {
    painter->setPen(color);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter->drawLine(line);
        painter->rotate(6.0);
    }
}
void AnalogClock::paintSecondsHand(QPainter *painter, const QPolygon &poly,
                                   const QColor &color) {
    painter->save();
    painter->rotate((m_time.second() + m_time.msec() / 1000.f) * 6.0);
    if (poly.size() == 2) {
        painter->setPen(color);
        painter->drawLine(poly[0], poly[1]);
    } else {
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawConvexPolygon(poly);
    }
    painter->restore();

    painter->setPen(Qt::NoPen);
}
