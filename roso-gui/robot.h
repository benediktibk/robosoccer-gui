#ifndef ROBOT_H
#define ROBOT_H

#include<vector>
#include<QPoint>
#include"obstacle.h"

class Robot
{
public:
	Robot(const std::vector<QPoint> &route, double radius);

	Obstacle getOwnRobotObstacle() const;
	double getOwnRadius() const;
	std::vector<QPoint> getRoute() const;

private:
	std::vector<QPoint> m_route;
	double m_radius;
};

#endif
