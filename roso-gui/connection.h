#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "obstacle.h"
#include "robot.h"

class QTcpSocket;
class Model;

class Connection :
		public QObject
{
	Q_OBJECT
public:
	Connection(Model &model);
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
	void parseData(QString data);
	void parseCompleteBlock();
	std::vector<Obstacle> parseObstacles(bool &error);
	Robot parseRobot(bool &error);

private:
	static QPointF parsePoint(QString const &string, bool &error);
	static double parseValue(QString const &string, bool &error);
	static Obstacle parseObstacle(QString const &string, bool &error);

private:
	QTcpSocket *m_socket;
	QStringList m_currentBlock;
	Model &m_model;
};

#endif
