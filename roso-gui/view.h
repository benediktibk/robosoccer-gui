#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QString>
#include <list>
#include <QGraphicsScene>

#define SCALE_FACTOR 100

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
	double worldToPixel(double worldCoordinate);

signals:
	void connectPressed();

protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void showEvent(QShowEvent *event);

private:
	void fitWholeAreaInView();

private slots:
	void connectPressedInternal();

private:
	Ui::Dialog *m_ui;
	QGraphicsScene *m_scene;
};

#endif
