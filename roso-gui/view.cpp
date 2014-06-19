#include "view.h"
#include "ui_dialog.h"
#include <QRectF>
#include <QColor>
#include <algorithm>
#include <QScrollBar>
#include <QPolygonF>
#include <QPainterPath>

using namespace std;

View::View() :
	m_ui(new Ui::Dialog),
	m_scene(new QGraphicsScene)
{
	m_ui->setupUi(this);
	m_ui->viewField->setScene(m_scene);
	drawPitch();
	test(); // To be removed

	QObject::connect(m_ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(connectPressedInternal()));
}

View::~View()
{
	delete m_ui;
	m_ui = 0;
	delete m_scene;
	m_scene = 0;
}

void View::setStatusConnected(bool isConnected)
{
	if(isConnected)
	{
		m_ui->labelConnectStatus->setText(QString("Connected"));
		m_ui->labelConnectStatus->setStyleSheet("QLabel { color : green; }");
		m_ui->pushButtonConnect->setText(QString("Disconnect"));
	}
	else
	{
		m_ui->labelConnectStatus->setText(QString("Disconnected"));
		m_ui->labelConnectStatus->setStyleSheet("QLabel { color : red; }");
		m_ui->pushButtonConnect->setText(QString("Connect"));
	}
}

void View::appendLogMessage(QString const &message)
{
	QPlainTextEdit &edit = *(m_ui->plainTextEditLog);
	QString plainText = edit.toPlainText() + message;
	int lineFeedCount = plainText.count('\n');
	int currentPosition = 0;

	for (int i = 0; i < lineFeedCount - 100; ++i)
		currentPosition = plainText.indexOf('\n', currentPosition) + 1;

	plainText = plainText.mid(currentPosition);
	edit.setPlainText(plainText);
	edit.verticalScrollBar()->setValue(edit.verticalScrollBar()->maximum());
}

QString View::getIpAdress() const
{
	return m_ui->plainTextEditIp->toPlainText();
}

unsigned int View::getPort() const
{
	return m_ui->plainTextEditPort->toPlainText().toUInt();
}

double View::worldToPixel(double worldCoordinate)
{
	return worldCoordinate*SCALE_FACTOR;
}

QPointF View::worldPointToPixlePoint(const QPointF &worldPoint)
{
	return worldPoint*SCALE_FACTOR;
}

void View::resizeEvent(QResizeEvent *)
{
	fitWholeAreaInView();
}

void View::showEvent(QShowEvent *)
{
	fitWholeAreaInView();
}

void View::fitWholeAreaInView()
{
	QRectF sceneRect = m_scene->sceneRect();
	sceneRect.setWidth(sceneRect.width()*1.1);
	sceneRect.setHeight(sceneRect.height()*1.1);
	m_ui->viewField->fitInView(sceneRect, Qt::KeepAspectRatio);
}

void View::drawRobot(const Robot &robot)
{
	QPointF robotPosition = robot.getOwnRobotObstacle().getPosition();
	double robotRadius = robot.getOwnRadius();

	vector<QPointF> route = robot.getRoute();
	QPolygonF poly;
	QPainterPath path;
	QPen pathPen;
	pathPen.setWidth(worldToPixel(2*robotRadius));
	pathPen.setColor(QColor(0, 255, 0, 128));
	pathPen.setJoinStyle(Qt::RoundJoin);

	poly << worldPointToPixlePoint(robotPosition);

	for(vector<QPointF>::const_iterator iterator = route.begin(); iterator != route.end(); ++iterator)
	{
		QPointF pathPoint = *iterator;
		poly << worldPointToPixlePoint(pathPoint);
	}

	path.addPolygon(poly);
	m_scene->addPath(path,pathPen,QBrush(Qt::transparent));

	QPointF topLeft = robotPosition - QPointF(robotRadius,robotRadius);
	QPointF bottomRight = robotPosition + QPointF(robotRadius,robotRadius);
	QRectF robotRect(worldPointToPixlePoint(topLeft),worldPointToPixlePoint(bottomRight));
	m_scene->addEllipse(robotRect, QPen(Qt::red), QBrush(Qt::red) );
}

void View::drawObstacles(const std::vector<Obstacle> &obstacles)
{
	for(vector<Obstacle>::const_iterator iterator = obstacles.begin(); iterator != obstacles.end(); ++iterator)
	{
		Obstacle currentObstacle = *iterator;
		QPointF currentObstaclePosition = currentObstacle.getPosition();
		double currentObstacleRadius = currentObstacle.getRadius();
		QPointF topLeft = currentObstaclePosition - QPointF(currentObstacleRadius,currentObstacleRadius);
		QPointF bottomRight = currentObstaclePosition + QPointF(currentObstacleRadius,currentObstacleRadius);
		QRectF currentObstacleRect(worldPointToPixlePoint(topLeft),worldPointToPixlePoint(bottomRight));
		m_scene->addEllipse(currentObstacleRect, QPen(Qt::red), QBrush(Qt::black));
	}
}

void View::drawPitch()
{
	QPainterPath roundedRectangle;
	QRectF playField(worldPointToPixlePoint(QPointF(-1.45,-0.9)),worldPointToPixlePoint(QPointF(1.45, 0.9)));
	roundedRectangle.addRoundedRect(playField,worldToPixel(0.3),worldToPixel(0.3));
	m_scene->addPath(roundedRectangle,QPen(Qt::black),QBrush(Qt::white));
	m_ui->viewField->setBackgroundBrush(QBrush(QColor(20,20,20,180)));
}

void View::connectPressedInternal()
{
	emit connectPressed();
}

void View::test()
{
	vector<QPointF> route;
	route.push_back(QPointF(0,0.5));
	route.push_back(QPointF(0.5,0.5));
	route.push_back(QPointF(1,0));
	route.push_back(QPointF(-1,0));
	Robot robot(route,0.05);
	drawRobot(robot);
	vector<Obstacle> obstacles;
	obstacles.push_back(Obstacle(QPointF(1.2,0),0.05));
	obstacles.push_back(Obstacle(QPointF(1.2,0.5),0.05));
	obstacles.push_back(Obstacle(QPointF(-0.9,0.6),0.05));
	obstacles.push_back(Obstacle(QPointF(-0.6,-0.4),0.025));
	drawObstacles(obstacles);
}
