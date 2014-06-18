#include "view.h"
#include "model.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View view;
	Model model;
	Controller controller(view, model);
	view.show();
	return a.exec();
}
