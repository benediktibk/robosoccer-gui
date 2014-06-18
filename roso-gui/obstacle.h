#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPoint>

class Obstacle
{
public:
	Obstacle(const QPoint &position, double radius);

	double getRadius() const;
	QPoint getPosition() const;

private:
	QPoint m_position;
	double m_radius;
};

#endif
