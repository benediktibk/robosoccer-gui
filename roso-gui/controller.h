#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>

class View;
class Model;
class Connection;
class Robot;
class QGraphicsEllipseItem;
class QGraphicsPathItem;
class QRectF;
class QPointF;

class Controller :
		public QObject
{
	Q_OBJECT

public:
	Controller(View &view, Model &model, Connection &connection);
	virtual ~Controller();

public slots:
	void appendLogMessages(QString message);
	void connectionEstablished();
	void connectionLost();
	void connectPressed();
	void updateRobotOne();
	void updateRobotTwo();
	void updateObstacles();

private:
	void updateRobot(Robot const &robot, QGraphicsEllipseItem &robotItem, QGraphicsPathItem &robotPathItem);
	void updateObstacleCount(size_t desiredCount);
	QRectF getRectFrom(QPointF const &position, double radius);

private:
	View &m_view;
	Model &m_model;
	Connection &m_connection;
	QGraphicsEllipseItem *m_robotOne;
	QGraphicsEllipseItem *m_robotTwo;
	QGraphicsPathItem *m_pathRobotOne;
	QGraphicsPathItem *m_pathRobotTwo;
	std::vector<QGraphicsEllipseItem*> m_obstacles;
	double m_penWidth;
};

#endif
