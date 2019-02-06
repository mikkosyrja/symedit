#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "symedit.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	SymEdit manager;

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("manager", &manager);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if ( engine.rootObjects().isEmpty() )
		return -1;

	return app.exec();
}
