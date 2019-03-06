#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QSettings>

#include "symedit.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setOrganizationName("Syrja");
	QCoreApplication::setOrganizationDomain("syrja.org");
	QCoreApplication::setApplicationName("SymEdit");
	QCoreApplication::setApplicationVersion("1.0");
	QSettings::setDefaultFormat(QSettings::IniFormat);

	QGuiApplication app(argc, argv);

	// register enumerations
	qmlRegisterUncreatableMetaObject(Operation::staticMetaObject,
		"Org.Syrja.Symbol.Operation", 1, 0, "Operation", "Error: only enums" );

	QCommandLineParser parser;
	parser.process(app);

	QString symbol;
	const QStringList arguments = parser.positionalArguments();
	if ( arguments.size() )
		symbol = arguments.at(0);

	// register manager
	SymEditManager manager(symbol);
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("manager", &manager);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if ( engine.rootObjects().isEmpty() )
		return -1;

	int result = app.exec();

	manager.SaveSettings();

	return result;
}
