#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>

class QTcpSocket;

class Connection :
		public QObject
{
	Q_OBJECT
public:
	Connection();
	virtual ~Connection();

	void open(QString const &ip, unsigned int port);
	void close();
	bool isConnected() const;

signals:
	void dataArrived(QString data);
	void connectionEstablished();
	void connectionLost();

private slots:
	void connectionEstablishedInternal();
	void connectionLostInternal();
	void dataArrivedInternal();

private:
	QTcpSocket *m_socket;
};

#endif
