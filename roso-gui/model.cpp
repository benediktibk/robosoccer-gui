#include "model.h"

using namespace std;

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
