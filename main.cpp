#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "symedit.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setOrganizationName("Syrja");
	QCoreApplication::setOrganizationDomain("syrja.org");
	QCoreApplication::setApplicationName("SymEdit");
	QSettings::setDefaultFormat(QSettings::IniFormat);

	QGuiApplication app(argc, argv);

	SymEditManager manager;

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("manager", &manager);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if ( engine.rootObjects().isEmpty() )
		return -1;

	int result = app.exec();

	manager.SaveSettings();

	return result;
}
