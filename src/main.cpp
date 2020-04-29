#include "views/QGameWindow.hpp"
#include <QtWidgets/QApplication>

#include <QtDebug>
#include <exception>

#include "opencv2/core.hpp"

int main(int argc, char *argv[])
{
	try {
		QApplication a(argc, argv);

		QGameWindow w;
		w.show();

		return a.exec();
	}
	catch (cv::Exception cvException) {
		qDebug() << cvException.what();
		qDebug() << cvException.msg.c_str();
	}
	
}
