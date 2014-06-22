#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QString>
#include <QPointF>
#include <QGraphicsScene>
#include <list>
#include <vector>
#include "model.h"
#include "robot.h"
#include "obstacle.h"

namespace Ui
{
	class Dialog;
}

class View :
		public QDialog
{
	Q_OBJECT

public:
	View();
	virtual ~View();

	void setStatusConnected(bool isConnected);
	void appendLogMessage(QString const &plainText);
	QString getIpAdress() const;
	unsigned int getPort() const;
	void updateGui(const Model &model);
	void test();

signals:
	void connectPressed();

protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void showEvent(QShowEvent *event);

private:
	void fitWholeAreaInView();
	void drawRobot(const Robot &robot);
	void drawObstacles(const std::vector<Obstacle> &obstacles);
	void drawPitch();
	void clearScene();

private slots:
	void connectPressedInternal();

private:
	Ui::Dialog *m_ui;
	QGraphicsScene *m_scene;
};

#endif
