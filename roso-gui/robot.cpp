#include "robot.h"

using namespace std;

Robot::Robot()
{ }

Robot::Robot(const vector<QPointF> &route, double radius):
	m_route(route),
	m_radius(radius)
{ }

Obstacle Robot::getOwnRobotObstacle() const
{
	QPointF ownPosition = m_route.front();
	return Obstacle(ownPosition, m_radius);
}

vector<QPointF> Robot::getRoute() const
{
	vector<QPointF> route = m_route;
	route.erase(route.begin());
	return route;
}

double Robot::getOwnRadius() const
{
	return m_radius;
}
