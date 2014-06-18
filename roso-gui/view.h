#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QString>
#include <list>
#include <QGraphicsScene>

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
	~View();

	void setStatusConnected(bool isConnected);
	void appendPlainText(QString plainText);
	QString getIpAdress() const;
	unsigned int getPort() const;

protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void showEvent(QShowEvent *event);

private:
	void fitWholeAreaInView();

private:
	Ui::Dialog *m_ui;
	QGraphicsScene *m_scene;
};

#endif
