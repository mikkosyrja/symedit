#include <QGuiApplication>
#include <QScreen>
#include <QClipboard>
#include <QSettings>
#include <QDesktopServices>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>

#include <QMessageBox>

#include "symedit.h"

//
//	settings functions
//
//! Constructor.
SymEditSettings::SymEditSettings()
{
	IntValues.emplace("SnapGrid", 5);
	IntValues.emplace("LineWidth", 1);
	IntValues.emplace("ColorIndex", 1);
	IntValues.emplace("FillItem", 0);
	IntValues.emplace("Alignment", 9);
	IntValues.emplace("SizeUnit", 0);
	IntValues.emplace("Tool", 1);

	RealValues.emplace("SymbolSize", 5.0);
	RealValues.emplace("TextSize", 0.0);

	TextValues.emplace("Language", "");
	TextValues.emplace("TextValue", "");
	TextValues.emplace("Directory", "");
}

//! Load settings.
void SymEditSettings::Load()
{
	QSettings settings;

	QSize size = QGuiApplication::primaryScreen()->size();
	Position.setX(settings.value("window/x", size.width() / 4).toInt());
	Position.setY(settings.value("window/y", size.height() / 6).toInt());
	Size.setWidth(settings.value("window/width", size.width() / 2).toInt());
	Size.setHeight(settings.value("window/height", size.height() * 2 / 3).toInt());

	TextValues.at("Directory") = settings.value("application/directory").toString();

	IntValues.at("SnapGrid") = settings.value("editor/snap", 5).toInt();
	IntValues.at("LineWidth") = settings.value("editor/width", 1).toInt();
	RealValues.at("SymbolSize") = settings.value("editor/symbol", 5.0).toDouble();
	TextValues.at("Language") = settings.value("editor/lang").toString();

//	IntValues.at("ColorIndex") = settings.value("editor/color", 1).toInt();
//	IntValues.at("FillItem") = settings.value("editor/fill", 0).toInt();
//	RealValues.at("TextSize") = settings.value("editor/size", 0.0).toDouble();
	IntValues.at("Alignment") = settings.value("editor/align", 9).toInt();
	IntValues.at("SizeUnit") = settings.value("editor/unit", 0).toInt();

	TextValues.at("TextValue") = settings.value("editor/text").toString();
	IntValues.at("Tool") = settings.value("editor/tool", 1).toInt();
}

//! Save settings.
void SymEditSettings::Save() const
{
	QSettings settings;

	settings.setValue("window/x", Position.x());
	settings.setValue("window/y", Position.y());
	settings.setValue("window/width", Size.width());
	settings.setValue("window/height", Size.height());

	settings.setValue("application/directory", TextValues.at("Directory"));

	settings.setValue("editor/snap", IntValues.at("SnapGrid"));
	settings.setValue("editor/width", IntValues.at("LineWidth"));
	settings.setValue("editor/symbol", RealValues.at("SymbolSize"));
	settings.setValue("editor/lang", TextValues.at("Language"));

	settings.setValue("editor/color", IntValues.at("ColorIndex"));
	settings.setValue("editor/fill", IntValues.at("FillItem"));
	settings.setValue("editor/size", RealValues.at("TextSize"));
	settings.setValue("editor/align", IntValues.at("Alignment"));
	settings.setValue("editor/unit", IntValues.at("SizeUnit"));

	settings.setValue("editor/text", TextValues.at("TextValue"));
	settings.setValue("editor/tool", IntValues.at("Tool"));
}

//
//	manager functions
//
//! Constructor.
/*!
	\param parent		Optional parent.
*/
SymEditManager::SymEditManager(QObject* parent) : QObject(parent)
{
	Settings.Load();
}

//! Constructor.
/*!
	\param filename		Symbol file name from command line.
	\param symbol		Symbol string from command line.
*/
SymEditManager::SymEditManager(const QString& filename, const QString& symbol)
	: QObject(nullptr), Filename(filename)
{
	Settings.Load();

	if ( !Filename.isEmpty() )
		open(Filename);

	if ( !symbol.isEmpty() )
		Symbol.Load(symbol);
}

//! Set window initialized.
void SymEditManager::setInitialized()
{
	Initialized = true;
}

//! Set window geometry.
/*!
	\param point		Window position.
	\param size			Window size.
*/
void SymEditManager::setGeometry(QPoint point, QSize size)
{
	if ( Initialized )
	{
		Settings.Position = point;
		Settings.Size = size;
	}
}

//! Get window position.
/*!
	\return				Window position.
*/
QPoint SymEditManager::getWindowPos() const
{
	return Settings.Position;
}

//! Get window size.
/*!
	\return				Window size.
*/
QSize SymEditManager::getWindowSize() const
{
	return Settings.Size;
}

//@{
//! Set setting value.
/*!
	\param name			Setting name.
	\param value		Setting value.
*/
void SymEditManager::setIntSetting(QString name, int value)
{
	if ( Settings.IntValues.find(name) != Settings.IntValues.end() )
		Settings.IntValues.at(name) = value;
}
void SymEditManager::setRealSetting(QString name, double value)
{
	if ( Settings.RealValues.find(name) != Settings.RealValues.end() )
		Settings.RealValues.at(name) = value;
}
void SymEditManager::setTextSetting(QString name, QString value)
{
	if ( Settings.TextValues.find(name) != Settings.TextValues.end() )
		Settings.TextValues.at(name) = value;
}
//@}

//@{
//! Get setting value.
/*!
	\param name			Setting name.
	\return				Setting value.
*/
int SymEditManager::getIntSetting(QString name) const
{
	if ( Settings.IntValues.find(name) != Settings.IntValues.end() )
		return Settings.IntValues.at(name);
	return 0;
}
double SymEditManager::getRealSetting(QString name) const
{
	if ( Settings.RealValues.find(name) != Settings.RealValues.end() )
		return Settings.RealValues.at(name);
	return 0;
}
QString SymEditManager::getTextSetting(QString name) const
{
	if ( Settings.TextValues.find(name) != Settings.TextValues.end() )
		return Settings.TextValues.at(name);
	return QString();
}
//@}

//! Get symbol as string.
/*!
	\param rich			Rich text with layout.
	\return				Symbol as string.
*/
QString SymEditManager::getSymbol(bool rich) const
{
	QString buffer;
	return Symbol.Save(buffer, rich);
}

//! Add point item.
/*!
	\param operation	Item operation.
	\param point		Point position.
	\param value		Item value.
	\param color		Color index.
	\param fill			Item area fill.
	\return				True for success.
*/
bool SymEditManager::addPointItem(int operation, QPoint point, int value, int color, int fill)
{
	undosave();
	Symbol.AddItem(static_cast<Operation::Type>(operation), point, point, value, color, fill);
	return true;
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Start position.
	\param end			End position.
	\param value		Item value.
	\param color		Color index.
	\param fill			Item area fill.
	\return				True for success.
*/
bool SymEditManager::addLineItem(int operation, QPoint point, QPoint end, int value, int color, int fill)
{
	undosave();
	Symbol.AddItem(static_cast<Operation::Type>(operation), point, end, value, color, fill);
	return true;
}

//! Add Text item.
/*!
	\param operation	Item operation.
	\param point		Text position.
	\param point		End position.
	\param text			Text string.
	\param size			Text size.
	\param unit			Size unit.
	\param color		Color index.
	\param align		Text alignment.
	\return				True for success.
*/
bool SymEditManager::addTextItem(int operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align)
{
	if ( !text.isEmpty() )
	{
		undosave();
		Symbol.AddItem(static_cast<Operation::Type>(operation), point, end, text, size, unit, color, align);
		return true;
	}
	return false;
}

//! Remove active item.
/*!
	\return				True for success.

	Activates previous or first item.
*/
bool SymEditManager::removeItem()
{
	if ( Symbol.GetItemCount() )
	{
		undosave();
		return Symbol.RemoveItem(Symbol.GetActiveIndex());
	}
	return false;
}

//! Get item count.
/*!
	\return				Item count.
*/
int SymEditManager::getItemCount() const
{
	return Symbol.GetItemCount();
}

//! Get item operation.
/*!
	\param index		Item index.
	\return				Item operation.
*/
int SymEditManager::getItemOperation(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Operation;
	return Operation::None;
}

//! Get item position.
/*!
	\param index		Item index.
	\return				Item position.
*/
QPoint SymEditManager::getItemPosition(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		if ( item.Operation == Operation::Rectangle )	// normalize to upper left
			return QPoint(std::min(item.End.x(), item.Point.x()), std::max(item.End.y(), item.Point.y()));
		return item.Point;
	}
	return QPoint(0, 0);
}

//@{
//! Get item data value.
/*!
	\param index		Item index.
	\return				Item value.
*/
int SymEditManager::getItemValue(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Value;
	return 0;
}
QPoint SymEditManager::getItemPoint(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		if ( item.Operation == Operation::Rectangle )	// normalize to lower right
			return QPoint(std::max(item.End.x(), item.Point.x()), std::min(item.End.y(), item.Point.y()));
		return item.End;
	}
	return QPoint(0, 0);
}
QString SymEditManager::getItemText(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Text;
	return "";
}
int SymEditManager::getItemColor(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Color;
	return 1;
}
int SymEditManager::getItemFill(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Fill;
	return 0;
}
int SymEditManager::getItemAlign(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Align;
	return 0;
}
double SymEditManager::getItemSize(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Size;
	return 0.0;
}
int SymEditManager::getItemUnit(int index) const
{
	if ( Symbol.GetItemCount() )
		return Symbol.GetItem(index).Unit;
	return 0;
}
//@}

//! Select item nearest to point.
/*!
	\param point		Point coordinates.
	\return				Nearest item index.
*/
int SymEditManager::selectItem(QPoint point) const
{
	return Symbol.SelectItem(point);
}

//! Set active item index.
/*!
	\param index		Active item index.
	\return				True for success.
*/
bool SymEditManager::setActiveIndex(int index)
{
	return Symbol.SetActiveIndex(index);
}

//! Get active item index.
/*!
	\return				Active item index.
*/
int SymEditManager::getActiveIndex() const
{
	return Symbol.GetActiveIndex();
}

//! Cut symbol to clipboard.
void SymEditManager::cutClipboard()
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
	{
		undosave();
		clipboard->setText(getSymbol(false));
		Symbol.Clear();
	}
}

//! Copy symbol to clipboard.
void SymEditManager::copyClipboard() const
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
		clipboard->setText(getSymbol(false));
}

//! Paste symbol from clipboard.
void SymEditManager::pasteClipboard()
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
	{
		undosave();
		Symbol.Load(clipboard->text());
	}
}

//! Rotate symbol.
/*!
	\param dir			Positive value rotates right, negative left.
*/
void SymEditManager::rotateSymbol(int dir)
{
	undosave();
	Symbol.RotateSymbol(dir);
}

//! Raise or lower item.
/*!
	\param dir			Positive value raises, negative lowers.
	\return				True for success.
*/
bool SymEditManager::raiseItem(int dir)
{
	if ( Symbol.GetItemCount() )
	{
		undosave();
		return Symbol.RaiseItem(dir);
	}
	return false;
}

//! Undo edit operation.
/*!
	\param undo			True undoes, false redoes.
	\return				True for success.
*/
bool SymEditManager::undo(bool undo)
{
	if ( undo )
	{
		if ( UndoStack.empty() )
			return false;

		QString buffer;
		Symbol.Save(buffer);
		RedoStack.push_back(buffer);

		Symbol.Load(UndoStack.back());
		UndoStack.pop_back();
		return true;
	}
	if ( RedoStack.empty() )
		return false;

	QString buffer;
	Symbol.Save(buffer);
	UndoStack.push_back(buffer);

	Symbol.Load(RedoStack.back());
	RedoStack.pop_back();
	return true;
}

//! Save item to undo stack.
void SymEditManager::undosave()
{
	QString buffer;
	Symbol.Save(buffer);
	UndoStack.push_back(buffer);
	RedoStack.clear();
}

//! Open help.
/*!
	\param topic		Help topic.
*/
void SymEditManager::help(QString topic) const
{
	Q_UNUSED(topic);
	QString path = QCoreApplication::applicationDirPath();
	path.append("/help/").append(Language).append("/symedit/index.html");
	if ( QFileInfo(path).exists() )		// release
		QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
	else	// development
	{
		path = QCoreApplication::applicationDirPath();
		path.append("/../threedee/help/").append(Language).append("/symedit/index.html");
		if ( QFileInfo(path).exists() )		// visual studio
			QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
		else	// qt creator
		{
			path = QCoreApplication::applicationDirPath();
			path.append("/../../symedit/help/").append(Language).append("/_build/html/index.html");
			if ( QFileInfo(path).exists() )		// windows
				QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
			else	// linux
			{
				path = QCoreApplication::applicationDirPath();
				path.append("/../symedit/help/").append(Language).append("/_build/html/index.html");
				if ( QFileInfo(path).exists() )
					QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
			}
		}
	}
}

//! Open symbol file.
/*!
	\param fileurl		File name as URL.
	\return				True for success.
*/
bool SymEditManager::open(QUrl fileurl)
{
	QString filestring = fileurl.toString();
	int index = filestring.lastIndexOf('/') + 1;
	QString directory = filestring.left(index);
	setTextSetting("Directory", directory);
	return open(fileurl.toLocalFile());
}

//! Save symbol file.
/*!
	\param fileurl		File name as URL.
	\return				True for success.
*/
bool SymEditManager::save(QUrl fileurl)
{
	QString filename = Filename;
	if ( !fileurl.isEmpty() )
	{
		QString filestring = fileurl.toString();
		int index = filestring.lastIndexOf('/') + 1;
		QString directory = filestring.left(index);
		setTextSetting("Directory", directory);
		filename = fileurl.toLocalFile();
	}
	return save(filename);
}

//! Check file name existence.
/*!
	\return				True for existing file name.
*/
bool SymEditManager::hasFilename() const
{
	return !Filename.isEmpty();
}

//! Get file name without path.
/*!
	\return				File name as url.
*/
QUrl SymEditManager::getFilename() const
{
	int index = Filename.lastIndexOf('/');
	return QUrl(Filename.mid(index + 1));
}

//! Open symbol file.
/*!
	\param filename		Full file path.
	\return				True for success.
*/
bool SymEditManager::open(const QString& filename)
{
	QFile file(filename);
	if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
	{
		QTextStream input(&file);
		Symbol.Load(input.readLine());
		Filename = filename;
		return true;
	}
	return false;
}

//! Save symbol file.
/*!
	\param filename		Full file path.
	\return				True for success.
*/
bool SymEditManager::save(const QString& filename)
{
	QFile file(filename);
	if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
	{
		QTextStream output(&file);
		output << getSymbol(false);
		Filename = filename;
		return true;
	}
	return false;
}

//! Set language.
/*!
	\param lang			Language abbreviation.
*/
void SymEditManager::setLanguage(QString lang)
{
	Language = lang;
}
