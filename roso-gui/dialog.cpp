#include "dialog.h"
#include "ui_dialog.h"
#include <QRectF>
#include <math.h>

using namespace std;

Dialog::Dialog() :
	QDialog(),
	m_ui(new Ui::Dialog),
	m_scene(new QGraphicsScene)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setScene(m_scene);
	QRectF playField(QPointF(-145,-90),QPointF(145,90));
	QRectF playField2(QPointF(-145/2,-90/2),QPointF(145/2,90/2));
	m_scene->addRect(playField);
	m_scene->addRect(playField2);
	m_ui->graphicsView->fitInView(m_scene->sceneRect(),Qt::KeepAspectRatio);
	//fitWholeAreaInView();
}

Dialog::~Dialog()
{
	delete m_ui;
	m_ui = 0;
	delete m_scene;
	m_scene = 0;
}

void Dialog::setStatusConnected(bool isConnected)
{
	if(isConnected)
		m_ui->labelConnectStatus->setText(QString("Connected"));
	else
		m_ui->labelConnectStatus->setText(QString("Disconnected"));
}

void Dialog::appendPlainText(QString plainText)
{
	m_ui->plainTextEditLog->appendPlainText(plainText);
}

QString Dialog::getIpAdress() const
{
	return m_ui->plainTextEditIp->toPlainText();
}

unsigned int Dialog::getPort() const
{
	return m_ui->plainTextEditPort->toPlainText().toUInt();
}

void Dialog::fitWholeAreaInView()
{
	double scaleX = m_ui->graphicsView->width()/m_scene->sceneRect().width();
	double scaleY = m_ui->graphicsView->height()/m_scene->sceneRect().height();
	double scaleMax = min(scaleX,scaleY);
	m_ui->graphicsView->scale(scaleMax, scaleMax);
}

