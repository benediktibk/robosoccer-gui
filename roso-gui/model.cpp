#include "model.h"
#include <QPoint>

Model::Model():
	m_robotOne(Robot(std::vector<QPoint>(),0.0)),
	m_robotTwo(Robot(std::vector<QPoint>(),0.0))
{
}

void Model::setRobotOne(const Robot &robotOne)
{
	m_robotOne = robotOne;
}

void Model::setRobotTwo(const Robot &robotTwo)
{
	m_robotTwo = robotTwo;
}

void Model::setObstacles(const std::vector<Obstacle> &obstacleVector)
{
	m_obstacles = obstacleVector;
}
