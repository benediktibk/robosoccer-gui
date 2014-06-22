#include "model.h"

using namespace std;

void Model::setRobotOne(const Robot &robotOne)
{
	m_robotOne = robotOne;
	emit robotOneChanged();
}

void Model::setRobotTwo(const Robot &robotTwo)
{
	m_robotTwo = robotTwo;
	emit robotTwoChanged();
}

void Model::setObstacles(const vector<Obstacle> &obstacleVector)
{
	m_obstacles = obstacleVector;
	emit obstaclesChanged();
}

std::vector<Obstacle> Model::getObstacles() const
{
	return m_obstacles;
}

Robot Model::getRobotOne() const
{
	return m_robotOne;
}

Robot Model::getRobotTwo() const
{
	return m_robotTwo;
}
