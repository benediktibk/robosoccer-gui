#include "dialog.h"
#include "ui_dialog.h"
#include <QRectF>
#include <algorithm>

using namespace std;

Dialog::Dialog() :
	QDialog(),
	m_ui(new Ui::Dialog),
	m_scene(new QGraphicsScene)
{
	m_ui->setupUi(this);
	m_ui->viewField->setScene(m_scene);
	QRectF playField(QPointF(-1.45,-0.9), QPointF(1.45, 0.9));
	m_scene->addRect(playField);
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

void Dialog::resizeEvent(QResizeEvent *)
{
	fitWholeAreaInView();
}

void Dialog::showEvent(QShowEvent *)
{
	fitWholeAreaInView();
}

void Dialog::fitWholeAreaInView()
{
	QRectF sceneRect = m_scene->sceneRect();
	sceneRect.setWidth(sceneRect.width()*1.1);
	sceneRect.setHeight(sceneRect.height()*1.1);
	m_ui->viewField->fitInView(sceneRect, Qt::KeepAspectRatio);
}

