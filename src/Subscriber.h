#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <qmqtt.h>

const QHostAddress EXAMPLE_HOST = QHostAddress::LocalHost;
const quint16 EXAMPLE_PORT = 1883;
const QString EXAMPLE_TOPIC = "koppi/test";

class Subscriber : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit Subscriber(const QHostAddress& host = EXAMPLE_HOST,
                        const quint16 port = EXAMPLE_PORT,
                        QObject* parent = nullptr);
    virtual ~Subscriber();

    QTextStream _qout;

public slots:
    void onConnected();
    void onSubscribed(const QString& topic);
    void onReceived(const QMQTT::Message& message);
};

#endif //SUBSCRIBER_H
