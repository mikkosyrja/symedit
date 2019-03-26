#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QSettings>
#include <QDir>

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

	// set base language translators
	QLocale locale;
	QTranslator backuptranslator, localetranslator, currenttranslator;
//	if ( backuptranslator.load(":/locale/symedit.fi_FI.qm") )
	if ( backuptranslator.load(":/locale/symedit.en_GB.qm") )
		QCoreApplication::installTranslator(&backuptranslator);
	if ( localetranslator.load(locale, ":/locale/symedit.") )
		QCoreApplication::installTranslator(&localetranslator);

	// register command line arguments
	QCommandLineParser parser;
	parser.addPositionalArgument("file", qtTrId("id_cli_symbol_file_name"));
	QCommandLineOption transferoption(QStringList() << "t" << "transfer", qtTrId("id_cli_transfer_file"));
	parser.addOption(transferoption);
	QCommandLineOption symboloption(QStringList() << "s" << "symbol",
		qtTrId("id_cli_symbol_description"), qtTrId("id_cli_symbol"));
	parser.addOption(symboloption);
	QCommandLineOption languageoption(QStringList() << "l" << "language",
		qtTrId("id_cli_language_description"), qtTrId("id_cli_language"));
	parser.addOption(languageoption);
	parser.addHelpOption();
	parser.process(app);

	// read command line arguments
	QString filename;
	const QStringList arguments = parser.positionalArguments();
	if ( arguments.size() )
	{
		if ( !QDir::isAbsolutePath(filename = arguments.at(0)) )
			filename.insert(0, '/').insert(0, QDir::currentPath());
	}
	bool transfer = parser.isSet(transferoption);
	QString symbol = parser.value(symboloption);

	// register enumerations
	qmlRegisterUncreatableMetaObject(Operation::staticMetaObject,
		"Org.Syrja.Symbol.Operation", 1, 0, "Operation", "Error: only enums" );

	// register manager
	QQmlApplicationEngine engine;
	SymEditManager manager(filename, symbol);
	engine.rootContext()->setContextProperty("manager", &manager);

	// set current translator
	QString language = manager.getTextSetting("Language");
	QString lang = parser.value(languageoption);
	if ( lang == "eng" || lang == "fin" )	//## use fi_FI and en_GB?
		language = lang;
	if ( currenttranslator.load(language == "fin" ? ":/locale/symedit.fi_FI.qm" : "") )
		QCoreApplication::installTranslator(&currenttranslator);
	manager.setLanguage(language);

	// start application
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if ( engine.rootObjects().isEmpty() )
		return -1;
	int result = app.exec();

	if ( transfer )
		manager.save(filename);
	manager.SaveSettings();

	return result;
}
