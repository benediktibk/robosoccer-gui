#include "robot.h"
#include <assert.h>

using namespace std;

Robot::Robot()
{ }

Robot::Robot(const vector<QPointF> &route, double radius, const vector<QPointF> &targets):
	m_route(route),
	m_radius(radius),
	m_targets(targets)
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

vector<QPointF> Robot::getTargets() const
{
	return m_targets;
}

double Robot::getRadius() const
{
	return m_radius;
}
