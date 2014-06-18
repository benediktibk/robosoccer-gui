#include "obstacle.h"

Obstacle::Obstacle(const QPoint &position, double radius):
	m_position(position),
	m_radius(radius)
{ }

double Obstacle::getRadius() const
{
	return m_radius;
}

QPoint Obstacle::getPosition() const
{
	return m_position;
}
