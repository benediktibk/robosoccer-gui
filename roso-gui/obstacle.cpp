#include "obstacle.h"

Obstacle::Obstacle()
{ }

Obstacle::Obstacle(const QPointF &position, double radius):
	m_position(position),
	m_radius(radius)
{ }

double Obstacle::getRadius() const
{
	return m_radius;
}

QPointF Obstacle::getPosition() const
{
	return m_position;
}
