#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <list>
#include <QGraphicsScene>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
	Q_OBJECT

public:
	explicit Dialog(QWidget *parent = 0);
	~Dialog();

	void setStatusConnected(bool isConnected);
	void appendPlainText(QString plainText);
	QString getIpAdress() const;
	unsigned int getPort() const;
private:
	void fitWholeAreaInView();
private:
	Ui::Dialog *ui;
	QGraphicsScene *m_scene;
};

#endif // DIALOG_H
