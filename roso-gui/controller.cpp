#include "controller.h"
#include "model.h"
#include "view.h"

using namespace std;

Controller::Controller(View &view, Model &model) :
	m_view(view),
	m_model(model)
{ }

Controller::~Controller()
{ }

void Controller::appendLogMessages(const QString &message)
{
	m_view.appendLogMessage(message);
}
