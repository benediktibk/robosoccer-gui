#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPoint>

class Obstacle
{
public:
	Obstacle();
	Obstacle(const QPointF &position, double radius);

	double getRadius() const;
	QPointF getPosition() const;

private:
	QPointF m_position;
	double m_radius;
};

#endif
