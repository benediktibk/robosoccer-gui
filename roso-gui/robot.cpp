#include "robot.h"

using namespace std;

Robot::Robot(const vector<QPoint> &route, double radius):
	m_route(route),
	m_radius(radius)
{ }

Obstacle Robot::getOwnRobotObstacle() const
{
	QPoint ownPosition = m_route.front();
	return Obstacle(ownPosition,m_radius);
}

vector<QPoint> Robot::getRoute() const
{
	return m_route;
}

double Robot::getOwnRadius() const
{
	return m_radius;
}
