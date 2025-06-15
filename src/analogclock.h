#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>
#include <QTime>

class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = nullptr);

    QSize sizeHint() const override {
        return QSize(400, 400);
    }

    QSize minimumSizeHint() const override {
        return QSize(200, 200);
    }

signals:
	void valueChanged(QTime time);
	
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void timerTimeout();

private:
    void paintDefault(QPainter *painter);

    void paintImg(QPainter *painter, const QString &imgpath);
    void paintHourHand(QPainter *painter, const QPolygon &poly,
                       const QColor &color);
    void paintHourMarkers(QPainter *painter, const QLine &line,
                          const QColor &color);
    void paintMinuteHand(QPainter *painter, const QPolygon &poly,
                         const QColor &color);
    void paintMinuteMarkers(QPainter *painter, const QLine &line,
                            const QColor &color);
    void paintSecondsHand(QPainter *painter, const QPolygon &poly,
                          const QColor &color);

	QTime m_time;
};

#endif
