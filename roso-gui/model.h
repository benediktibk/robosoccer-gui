#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "obstacle.h"
#include "robot.h"

class Model
{
public:
	Model();

	void setRobotOne(const Robot &robotOne);
	void setRobotTwo(const Robot &robotTwo);
	void setObstacles(const std::vector<Obstacle> &obstacleVector);

private:
	Robot m_robotOne;
	Robot m_robotTwo;
	std::vector<Obstacle> m_obstacles;
};

#endif
