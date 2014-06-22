#include "view.h"
#include "ui_dialog.h"
#include <QRectF>
#include <QColor>
#include <algorithm>
#include <QScrollBar>
#include <QPolygonF>
#include <QPainterPath>


#include <unistd.h>
using namespace std;

View::View() :
	m_ui(new Ui::Dialog),
	m_scene(new QGraphicsScene)
{
	m_ui->setupUi(this);
	m_ui->viewField->setScene(m_scene);
	drawPitch();
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

void View::addItem(QGraphicsItem *item)
{
	m_scene->addItem(item);
}

void View::removeItem(QGraphicsItem *item)
{
	m_scene->removeItem(item);
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

void View::drawPitch()
{
	QPainterPath roundedRectangle;
	QRectF playField(QPointF(-1.45, -0.9), QPointF(1.45, 0.9));
	roundedRectangle.addRoundedRect(playField, 0.3, 0.3);
	m_scene->addPath(roundedRectangle,QPen(Qt::black),QBrush(Qt::white));
	m_ui->viewField->setBackgroundBrush(QBrush(QColor(20, 20, 20, 180)));

	QRectF goalZoneLeft(QPointF(-1.45, -0.35), QPointF(-1.45 + 0.245, 0.35));
	QRectF goalZoneRight(QPointF(1.45 - 0.245, -0.35), QPointF(1.45, 0.35));
	QRectF goalLeft(QPointF(-1.7, -0.2), QPointF(-1.45, 0.2));
	QRectF goalRight(QPointF(1.45, -0.2), QPointF(1.7, 0.2));
	m_scene->addRect(goalZoneLeft, QPen(Qt::black), QBrush(QColor(150, 150, 150)));
	m_scene->addRect(goalZoneRight, QPen(Qt::black), QBrush(QColor(150, 150, 150)));
	m_scene->addRect(goalLeft, QPen(Qt::black), QBrush(QColor(150, 150, 150)));
	m_scene->addRect(goalRight, QPen(Qt::black), QBrush(QColor(150, 150, 150)));
}

void View::connectPressedInternal()
{
	emit connectPressed();
}
