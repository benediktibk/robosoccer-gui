#include "robot.h"
#include <assert.h>

using namespace std;

Robot::Robot()
{ }

Robot::Robot(const vector<QPointF> &route, double radius):
	m_route(route),
	m_radius(radius)
{ }

bool Robot::isValid() const
{
	return !m_route.empty();
}

QPointF Robot::getPosition() const
{
	assert(isValid());
	return m_route.front();
}

vector<QPointF> Robot::getRoute() const
{
	return m_route;
}

double Robot::getRadius() const
{
	return m_radius;
}
