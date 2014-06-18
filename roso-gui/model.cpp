#include "model.h"
#include <QPoint>

using namespace std;

Model::Model():
	m_robotOne(Robot(vector<QPoint>(), 0)),
	m_robotTwo(Robot(vector<QPoint>(), 0))
{ }

void Model::setRobotOne(const Robot &robotOne)
{
	m_robotOne = robotOne;
}

void Model::setRobotTwo(const Robot &robotTwo)
{
	m_robotTwo = robotTwo;
}

void Model::setObstacles(const vector<Obstacle> &obstacleVector)
{
	m_obstacles = obstacleVector;
}
