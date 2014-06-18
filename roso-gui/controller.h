#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class View;
class Model;
class Connection;

class Controller :
		public QObject
{
	Q_OBJECT

public:
	Controller(View &view, Model &model, Connection &connection);
	virtual ~Controller();

public slots:
	void appendLogMessages(QString message);
	void connectionEstablished();
	void connectionLost();
	void open();

private:
	View &m_view;
	Model &m_model;
	Connection &m_connection;
};

#endif
