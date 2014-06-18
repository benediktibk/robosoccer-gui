#include "view.h"
#include "model.h"
#include "controller.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View view;
	Model model;
	Connection connection;
	Controller controller(view, model, connection);

	view.show();
	return a.exec();
}
