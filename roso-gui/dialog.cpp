#include "dialog.h"
#include "ui_dialog.h"
#include <QRectF>
#include <math.h>

using namespace std;

Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog),
	m_scene(new QGraphicsScene)
{
	ui->setupUi(this);
	ui->graphicsView->setScene(m_scene);
	QRectF playField(QPointF(-145,-90),QPointF(145,90));
	QRectF playField2(QPointF(-145/2,-90/2),QPointF(145/2,90/2));
	m_scene->addRect(playField);
	m_scene->addRect(playField2);
	ui->graphicsView->fitInView(m_scene->sceneRect(),Qt::KeepAspectRatio);
	//fitWholeAreaInView();
}

Dialog::~Dialog()
{
	delete ui;
	delete m_scene;
}

void Dialog::setStatusConnected(bool isConnected)
{
	if(isConnected)
		ui->labelConnectStatus->setText(QString("Connected"));
	else
		ui->labelConnectStatus->setText(QString("Disconnected"));
}

void Dialog::appendPlainText(QString plainText)
{
	ui->plainTextEditLog->appendPlainText(plainText);
}

QString Dialog::getIpAdress() const
{
	return ui->plainTextEditIp->toPlainText();
}

unsigned int Dialog::getPort() const
{
	return ui->plainTextEditPort->toPlainText().toUInt();
}

void Dialog::fitWholeAreaInView()
{
	double scaleX = ui->graphicsView->width()/m_scene->sceneRect().width();
	double scaleY = ui->graphicsView->height()/m_scene->sceneRect().height();
	double scaleMax = min(scaleX,scaleY);
	ui->graphicsView->scale(scaleMax,scaleMax);
}

