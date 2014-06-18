#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class View;
class Model;

class Controller :
		public QObject
{
	Q_OBJECT

public:
	Controller(View &view, Model &model);
	virtual ~Controller();

public slots:
	void appendLogMessages(QString const &message);

private:
	View &m_view;
	Model &m_model;
};

#endif
