#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
}

Dialog::~Dialog()
{
	delete ui;
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

