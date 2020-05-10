// Qt
#include <QtWidgets/QApplication>

// Yams
#include "QYams.hpp"


int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	QYams yams;
	yams.show();

	return application.exec();
}
