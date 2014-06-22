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
	void setRobotOne(const Robot &robotOne);
	void setRobotTwo(const Robot &robotTwo);
	void setObstacles(const std::vector<Obstacle> &obstacleVector);
	std::vector<Obstacle> getObstacles() const;
	Robot getRobotOne() const;
	Robot getRobotTwo() const;

signals:
	void robotOneChanged();
	void robotTwoChanged();
	void obstaclesChanged();

private:
	Robot m_robotOne;
	Robot m_robotTwo;
	std::vector<Obstacle> m_obstacles;
};

#endif
