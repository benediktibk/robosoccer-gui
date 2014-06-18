#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QObject>
#include "obstacle.h"
#include "robot.h"

class Model :
		public QObject
{
	Q_OBJECT

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
