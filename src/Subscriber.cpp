#include "Subscriber.h"

#include <ostream>
#include <QTimer>

Subscriber::Subscriber(const QHostAddress& host,
                        const quint16 port,
                        QObject* parent)
        : QMQTT::Client(host, port, parent)
        , _qout(stdout)
    {
        connect(this, &Subscriber::connected, this, &Subscriber::onConnected);
        connect(this, &Subscriber::subscribed, this, &Subscriber::onSubscribed);
        connect(this, &Subscriber::received, this, &Subscriber::onReceived);

        _qout << "Subscribing" << Qt::endl;
    };

    Subscriber::~Subscriber() {}

void Subscriber::onConnected()
{
    _qout << "connected" << Qt::endl;
    subscribe(EXAMPLE_TOPIC, 0);
}

void Subscriber::onSubscribed(const QString& topic)
{
    _qout << "subscribed " << topic << Qt::endl;
}

void Subscriber::onReceived(const QMQTT::Message& message)
{
    _qout << "publish received: \"" << QString::fromUtf8(message.payload())
          << "\"" << Qt::endl;
}