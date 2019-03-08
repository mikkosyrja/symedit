#include <QGuiApplication>
#include <QClipboard>
#include <QSettings>

#include <QDesktopServices>
#include <QUrl>

#include "symedit.h"

//
//	settings functions
//
//! Constructor.
SymEditSettings::SymEditSettings()
{
	IntValues.emplace("FillItem", 0);
	IntValues.emplace("Alignment", 9);
	IntValues.emplace("LineWidth", 1);
	IntValues.emplace("TextSize", 1);
	IntValues.emplace("SnapGrid", 5);
	IntValues.emplace("Tool", 1);

	TextValues.emplace("TextValue", "");
}

//! Load settings.
void SymEditSettings::Load()
{
	QSettings settings;

	Position.setX(settings.value("window/x", 100).toInt());
	Position.setY(settings.value("window/y", 100).toInt());
	Size.setWidth(settings.value("window/width", 500).toInt());
	Size.setHeight(settings.value("window/height", 500).toInt());

	IntValues.at("FillItem") = settings.value("editor/fill", 0).toInt();
	IntValues.at("Alignment") = settings.value("editor/align", 9).toInt();
	IntValues.at("LineWidth") = settings.value("editor/width", 1).toInt();
	IntValues.at("TextSize") = settings.value("editor/size", 1).toInt();
	IntValues.at("SnapGrid") = settings.value("editor/snap", 5).toInt();
	IntValues.at("Tool") = settings.value("editor/tool", 1).toInt();

	TextValues.at("TextValue") = settings.value("editor/text").toString();
}

//! Save settings.
void SymEditSettings::Save() const
{
	QSettings settings;

	settings.setValue("window/x", Position.x());
	settings.setValue("window/y", Position.y());
	settings.setValue("window/width", Size.width());
	settings.setValue("window/height", Size.height());

	settings.setValue("editor/fill", IntValues.at("FillItem"));
	settings.setValue("editor/align", IntValues.at("Alignment"));
	settings.setValue("editor/width", IntValues.at("LineWidth"));
	settings.setValue("editor/size", IntValues.at("TextSize"));
	settings.setValue("editor/snap", IntValues.at("SnapGrid"));
	settings.setValue("editor/tool", IntValues.at("Tool"));

	settings.setValue("editor/text", TextValues.at("TextValue"));
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
	: SymEditManager(nullptr)
{
	if ( !filename.isEmpty() )
	{
		//## load file
	}

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
QString SymEditManager::getTextSetting(QString name) const
{
	if ( Settings.TextValues.find(name) != Settings.TextValues.end() )
		return Settings.TextValues.at(name);
	return QString();
}
//@}

//! Get symbol as string.
/*!
	\return				Symbol as string.
*/
QString SymEditManager::getSymbol() const
{
	QString buffer;
	return Symbol.Save(buffer);
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item value.
	\param fill			Item area fill.
	\return				True for success.
*/
bool SymEditManager::addValueItem(int operation, QPoint point, int value, int fill)
{
	undosave();
	Symbol.AddItem(static_cast<Operation::Type>(operation), point, value, fill);
	return true;
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item value.
	\param fill			Item area fill.
	\return				True for success.
*/
bool SymEditManager::addPointItem(int operation, QPoint point, QPoint value, int fill)
{
	undosave();
	Symbol.AddItem(static_cast<Operation::Type>(operation), point, value, fill);
	return true;
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item text value.
	\param align		Item text alignment.
	\return				True for success.
*/
bool SymEditManager::addTextItem(int operation, QPoint point, QString value, int align)
{
	if ( !value.isEmpty() )
	{
		undosave();
		Symbol.AddItem(static_cast<Operation::Type>(operation), point, value, align);
		return true;
	}
	return false;
}

//! Remove active item.
/*!
	\return				True for success.
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
	{
		const auto& item = Symbol.GetItem(index);
		return item.Operation;
	}
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
			return QPoint(std::min(item.Value.x(), item.Point.x()), std::max(item.Value.y(), item.Point.y()));
		return item.Point;
	}
	return QPoint(0, 0);
}

//! Get item int value.
/*!
	\param index		Item index.
	\return				Item value.
*/
int SymEditManager::getItemValue(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		return item.Value.x();
	}
	return 0;
}

//! Get item point value.
/*!
	\param index		Item index.
	\return				Item value.
*/
QPoint SymEditManager::getItemPoint(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		if ( item.Operation == Operation::Rectangle )	// normalize to lower right
			return QPoint(std::max(item.Value.x(), item.Point.x()), std::min(item.Value.y(), item.Point.y()));
		return item.Value;
	}
	return QPoint(0, 0);
}

//! Get item text value.
/*!
	\param index		Item index.
	\return				Item value.
*/
QString SymEditManager::getItemText(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		return item.Text;
	}
	return "";
}

//
int SymEditManager::getItemFill(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		return item.Fill;
	}
	return 0;
}

//
int SymEditManager::getItemAlign(int index) const
{
	if ( Symbol.GetItemCount() )
	{
		const auto& item = Symbol.GetItem(index);
		return item.Align;
	}
	return 0;
}

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
*/
void SymEditManager::setActiveIndex(int index)
{
	Symbol.SetActiveIndex(index);
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
		clipboard->setText(getSymbol());
		Symbol.Clear();
	}
}

//! Copy symbol to clipboard.
void SymEditManager::copyClipboard() const
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
		clipboard->setText(getSymbol());
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

//! Open symbol file.
bool SymEditManager::open()
{
	//##
	return false;
}

//! Save symbol file.
bool SymEditManager::save()
{
	//##
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
	QString path = QCoreApplication::applicationDirPath();
	path.append("/help/fin/index.html");
	QDesktopServices::openUrl(QUrl(path));
//	QDesktopServices::openUrl(QUrl("https://qt.io/"));
}
