#include "controller.h"
#include "model.h"
#include "view.h"
#include "connection.h"
#include <QGraphicsEllipseItem>

using namespace std;

Controller::Controller(View &view, Model &model, Connection &connection) :
	m_view(view),
	m_model(model),
	m_connection(connection),
	m_robotOne(new QGraphicsEllipseItem()),
	m_robotTwo(new QGraphicsEllipseItem())
{
	QObject::connect(&m_connection, SIGNAL(dataArrived(QString)), this, SLOT(appendLogMessages(QString)));
	QObject::connect(&m_connection, SIGNAL(connectionEstablished()), this, SLOT(connectionEstablished()));
	QObject::connect(&m_connection, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
	QObject::connect(&m_view, SIGNAL(connectPressed()), this, SLOT(connectPressed()));
	QObject::connect(&m_model, SIGNAL(robotOneChanged()), this, SLOT(updateRobotOne()));
	QObject::connect(&m_model, SIGNAL(robotTwoChanged()), this, SLOT(updateRobotTwo()));
	QObject::connect(&m_model, SIGNAL(obstaclesChanged()), this, SLOT(updateObstacles()));

	m_robotOne->setPen(QPen(Qt::red));
	m_robotOne->setBrush(QBrush(Qt::red));
	m_robotTwo->setPen(QPen(Qt::red));
	m_robotTwo->setBrush(QBrush(Qt::red));

	m_view.addItem(m_robotOne);
	m_view.addItem(m_robotTwo);
}

Controller::~Controller()
{
	m_view.removeItem(m_robotOne);
	delete m_robotOne;
	m_robotOne = 0;

	m_view.removeItem(m_robotTwo);
	delete m_robotTwo;
	m_robotTwo = 0;

	updateObstacleCount(0);
}

void Controller::appendLogMessages(QString message)
{
	m_view.appendLogMessage(message);
}

void Controller::connectionEstablished()
{
	m_view.setStatusConnected(true);
}

void Controller::connectionLost()
{
	m_view.setStatusConnected(false);
}

void Controller::connectPressed()
{
	if (m_connection.isConnected())
		m_connection.close();
	else
	{
		QString ip = m_view.getIpAdress();
		unsigned int port = m_view.getPort();
		m_connection.open(ip, port);
	}
}

void Controller::updateRobotOne()
{
	Robot robot = m_model.getRobotOne();
	updateRobot(robot, *m_robotOne);
}

void Controller::updateRobotTwo()
{
	Robot robot = m_model.getRobotTwo();
	updateRobot(robot, *m_robotTwo);
}

void Controller::updateObstacles()
{
	vector<Obstacle> obstacles = m_model.getObstacles();
	updateObstacleCount(obstacles.size());

	for (size_t i = 0; i < obstacles.size(); ++i)
	{
		Obstacle const &obstacle = obstacles[i];
		QGraphicsEllipseItem &obstacleItem = *(m_obstacles[i]);
		QRectF rectangle = getRectFrom(obstacle.getPosition(), obstacle.getRadius());
		obstacleItem.setRect(rectangle);
	}
}

void Controller::updateRobot(const Robot &robot, QGraphicsEllipseItem &robotItem)
{
	vector<QPointF> route = robot.getRoute();

	if (route.empty())
		return;

	QPointF position = route.front();
	double radius = robot.getOwnRadius();
	QRectF robotRect = getRectFrom(position, radius);
	robotItem.setRect(robotRect);
}

void Controller::updateObstacleCount(size_t desiredCount)
{
	m_obstacles.reserve(desiredCount);

	while (desiredCount > m_obstacles.size())
	{
		QGraphicsEllipseItem *obstacle = new QGraphicsEllipseItem();
		obstacle->setPen(QPen(Qt::red));
		obstacle->setBrush(QBrush(Qt::black));
		m_view.addItem(obstacle);
		m_obstacles.push_back(obstacle);
	}

	while (desiredCount < m_obstacles.size())
	{
		QGraphicsEllipseItem *obstacle = m_obstacles.back();
		m_view.removeItem(obstacle);
		delete obstacle;
		m_obstacles.pop_back();
	}
}

QRectF Controller::getRectFrom(const QPointF &position, double radius)
{
	QPointF topLeft = position - QPointF(radius, radius);
	QPointF bottomRight = position + QPointF(radius, radius);
	return QRectF(topLeft, bottomRight);
}
