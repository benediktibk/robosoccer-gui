#ifndef ROBOT_H
#define ROBOT_H

#include<vector>
#include<QPoint>
#include"obstacle.h"

class Robot
{
public:
	Robot();
	Robot(const std::vector<QPointF> &route, double radius, const std::vector<QPointF> &targets);

	bool isValid() const;
	QPointF getPosition() const;
	double getRadius() const;
	std::vector<QPointF> getRoute() const;
	std::vector<QPointF> getTargets() const;

private:
	std::vector<QPointF> m_route;
	double m_radius;
	std::vector<QPointF> m_targets;
};

#endif
