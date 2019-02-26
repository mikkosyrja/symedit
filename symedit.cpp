#include <QGuiApplication>
#include <QClipboard>
#include <QSettings>

#include "symedit.h"

//
//	settings functions
//
//! Constructor.
SymEditSettings::SymEditSettings()
{
	Values.emplace("FillItem", 0);
	Values.emplace("Alignment", 9);
	Values.emplace("LineWidth", 1);
	Values.emplace("TextSize", 1);
	Values.emplace("SnapGrid", 5);
	Values.emplace("Tool", 1);
}

//! Load settings.
void SymEditSettings::Load()
{
	QSettings settings;

	Position.setX(settings.value("window/x", 100).toInt());
	Position.setY(settings.value("window/y", 100).toInt());
	Size.setWidth(settings.value("window/width", 500).toInt());
	Size.setHeight(settings.value("window/height", 500).toInt());

	Values.at("FillItem") = settings.value("editor/fill", 0).toInt();
	Values.at("Alignment") = settings.value("editor/align", 9).toInt();
	Values.at("LineWidth") = settings.value("editor/width", 1).toInt();
	Values.at("TextSize") = settings.value("editor/size", 1).toInt();
	Values.at("SnapGrid") = settings.value("editor/snap", 5).toInt();
	Values.at("Tool") = settings.value("editor/tool", 1).toInt();
}

//! Save settings.
void SymEditSettings::Save() const
{
	QSettings settings;

	settings.setValue("window/x", Position.x());
	settings.setValue("window/y", Position.y());
	settings.setValue("window/width", Size.width());
	settings.setValue("window/height", Size.height());

	settings.setValue("editor/fill", Values.at("FillItem"));
	settings.setValue("editor/align", Values.at("Alignment"));
	settings.setValue("editor/width", Values.at("LineWidth"));
	settings.setValue("editor/size", Values.at("TextSize"));
	settings.setValue("editor/snap", Values.at("SnapGrid"));
	settings.setValue("editor/tool", Values.at("Tool"));
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

	Symbol.Load("U00,00;R50;U-35,-35;D35,35;U-35,35;D35,-35;");		//##
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

//! Set setting value.
/*!
	\param name			Setting name.
	\param value		Setting value.
*/
void SymEditManager::setIntSetting(QString name, int value)
{
	if ( Settings.Values.find(name) != Settings.Values.end() )
		Settings.Values.at(name) = value;
}

//! Get setting value.
/*!
	\param name			Setting name.
	\return				Setting value.
*/
int SymEditManager::getIntSetting(QString name) const
{
	if ( Settings.Values.find(name) != Settings.Values.end() )
		return Settings.Values.at(name);
	return 0;
}

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
	\return				Reference to item.
*/
void SymEditManager::addValueItem(int operation, QPoint point, int value, int fill)
{
	undosave();
	Symbol.AddItem(operation, point, value, fill);
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item value.
	\param fill			Item area fill.
	\return				Reference to item.
*/
void SymEditManager::addPointItem(int operation, QPoint point, QPoint value, int fill)
{
	undosave();
	Symbol.AddItem(operation, point, value, fill);
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item text value.
	\param align		Item text alignment.
	\return				Reference to item.
*/
void SymEditManager::addTextItem(int operation, QPoint point, QString value, int align)
{
	undosave();
	Symbol.AddItem(operation, point, value, align);
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
	return 0;
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
		if ( item.Operation == 'B' )	// normalize to upper left
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
		if ( item.Operation == 'B' )	// normalize to lower right
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
