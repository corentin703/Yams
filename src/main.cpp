#include "QYams.hpp"
#include <QtWidgets/QApplication>

//#include <QtDebug>
//#include <exception>

int main(int argc, char *argv[])
{
	/*try {
		QApplication a(argc, argv);

		QYams w;
		w.show();

		return a.exec();
	}
	catch (std::exception exception) {
		qDebug() << exception.what();
	}*/


	QApplication a(argc, argv);

	QYams w;
	w.show();

	return a.exec();
}
