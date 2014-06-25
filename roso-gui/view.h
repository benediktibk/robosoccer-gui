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
	void addItem(QGraphicsItem *item);
	void removeItem(QGraphicsItem *item);

signals:
	void connectPressed();

protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void showEvent(QShowEvent *event);

private:
	void fitWholeAreaInView();
	void drawPitch();

private slots:
	void connectPressedInternal();

private:
	Ui::Dialog *m_ui;
	QGraphicsScene *m_scene;
	const double m_penWidth;
	const QRectF m_boundingRectangle;
};

#endif
