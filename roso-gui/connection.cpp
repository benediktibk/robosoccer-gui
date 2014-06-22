#include "connection.h"
#include "model.h"
#include <QtNetwork/QTcpSocket>
#include <QIODevice>

using namespace std;

Connection::Connection(Model &model) :
	m_socket(new QTcpSocket()),
	m_model(model)
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

void Connection::close()
{
	m_socket->close();
}

bool Connection::isConnected() const
{
	return m_socket->isOpen();
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
	parseData(dataString);
}

void Connection::parseData(QString data)
{
	QStringList lines = data.split('\n');

	for (int i = 0; i < lines.size(); ++i)
	{
		const QString &line = lines.at(i);

		if (line == "")
			parseCompleteBlock();
		else
			m_currentBlock.append(line);
	}
}

void Connection::parseCompleteBlock()
{
	if (m_currentBlock.size() == 0)
		return;

	QString firstLine = m_currentBlock.front();
	bool error;

	if (firstLine == "obstacles")
	{
		vector<Obstacle> obstacles = parseObstacles(error);
		if (!error)
			m_model.setObstacles(obstacles);
	}
	else if (firstLine == "robot one")
	{
		Robot robot = parseRobot(error);
		if (!error)
			m_model.setRobotOne(robot);
	}
	else if (firstLine == "robot two")
	{
		Robot robot = parseRobot(error);
		if (!error)
			m_model.setRobotTwo(robot);
	}

	m_currentBlock.clear();
}

vector<Obstacle> Connection::parseObstacles(bool &error)
{
	vector<Obstacle> obstacles;

	for (int i = 1; i < m_currentBlock.size(); ++i)
	{
		QString const &line = m_currentBlock.at(i);
		Obstacle obstacle = parseObstacle(line, error);
		if (error)
			return vector<Obstacle>();

		obstacles.push_back(obstacle);
	}

	return obstacles;
}

Robot Connection::parseRobot(bool &error)
{
	if (m_currentBlock.size() < 3)
	{
		error = true;
		return Robot();
	}

	QString const &secondLine = m_currentBlock.at(1);
	QString widthString = secondLine.mid(7);

	double width = parseValue(widthString, error);
	if (error)
		return Robot();

	vector<QPointF> route;
	for (int i = 2; i < m_currentBlock.size(); ++i)
	{
		QString const &line = m_currentBlock.at(i);
		QPointF point = parsePoint(line, error);
		if (error)
			return Robot();
		route.push_back(point);
	}

	return Robot(route, width);
}

QPointF Connection::parsePoint(const QString &string, bool &error)
{
	int commaPosition = string.indexOf(',');
	int xStart = 1;
	int xEnd = commaPosition - 1;
	int yStart = commaPosition + 2;
	int yEnd = string.size() - 2;
	QString xString = string.mid(xStart, xEnd - xStart + 1);
	QString yString = string.mid(yStart, yEnd - yStart + 1);

	double x = parseValue(xString, error);
	if (error)
		return QPointF();

	double y = parseValue(yString, error);
	if (error)
		return QPointF();

	return QPointF(x, y);
}

double Connection::parseValue(const QString &string, bool &error)
{
	bool isOk;
	double result = string.toDouble(&isOk);
	error = !isOk;
	return result;
}

Obstacle Connection::parseObstacle(const QString &string, bool &error)
{
	int firstCommaPosition = string.indexOf(',');
	int secondCommaPosition = string.indexOf(',', firstCommaPosition + 1);
	QString pointString = string.left(secondCommaPosition);
	QString radiusString = string.mid(secondCommaPosition + 2);

	QPointF center = parsePoint(pointString, error);
	if (error)
		return Obstacle();

	double radius = parseValue(radiusString, error);
	if (error)
		return Obstacle();

	return Obstacle(center, radius);
}
