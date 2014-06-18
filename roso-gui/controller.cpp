#include "controller.h"
#include "model.h"
#include "view.h"
#include "connection.h"

using namespace std;

Controller::Controller(View &view, Model &model, Connection &connection) :
	m_view(view),
	m_model(model),
	m_connection(connection)
{
	QObject::connect(&m_connection, SIGNAL(dataArrived(QString)), this, SLOT(appendLogMessages(QString)));
	QObject::connect(&m_connection, SIGNAL(connectionEstablished()), this, SLOT(connectionEstablished()));
	QObject::connect(&m_connection, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
	QObject::connect(&m_view, SIGNAL(connectPressed()), this, SLOT(connectPressed()));
}

Controller::~Controller()
{ }

void Controller::appendLogMessages(QString message)
{
	m_view.appendLogMessage(message);
}

void Controller::connectionEstablished()
{
	m_view.setStatusConnected(true);
}

void Controller::connectionLost()
{
	m_view.setStatusConnected(false);
}

void Controller::connectPressed()
{
	if (m_connection.isConnected())
		m_connection.close();
	else
	{
		QString ip = m_view.getIpAdress();
		unsigned int port = m_view.getPort();
		m_connection.open(ip, port);
	}
}
