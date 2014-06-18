#include "connection.h"
#include <QtNetwork/QTcpSocket>
#include <QIODevice>

Connection::Connection() :
	m_socket(new QTcpSocket())
{
	connect(m_socket, SIGNAL(connected()), this, SLOT(connectionEstablishedInternal()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(connectionLostInternal()));
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(dataArrivedInternal()));
}

Connection::~Connection()
{
	delete m_socket;
	m_socket = 0;
}

void Connection::open(const QString &ip, unsigned int port)
{
	m_socket->connectToHost(ip, port, QIODevice::ReadOnly);
}

void Connection::connectionEstablishedInternal()
{
	emit connectionEstablished();
}

void Connection::connectionLostInternal()
{
	emit connectionLost();
}

void Connection::dataArrivedInternal()
{
	QByteArray dataByteArray = m_socket->readAll();
	QString dataString(dataByteArray);
	emit dataArrived(dataString);
}
