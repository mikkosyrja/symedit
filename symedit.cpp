#include <QGuiApplication>
#include <QClipboard>
#include <QSettings>

#include "symedit.h"

//
//	settings functions
//
//! Constructor.
SymEditSettings::SymEditSettings() : FillItem(false), Alignment(9), LineWidth(1), SnapGrid(5), Tool(1)
{

}

//! Load settings.
void SymEditSettings::Load()
{
	QSettings settings;

	Position.setX(settings.value("window/x", 100).toInt());
	Position.setY(settings.value("window/y", 100).toInt());
	Size.setWidth(settings.value("window/width", 500).toInt());
	Size.setHeight(settings.value("window/height", 500).toInt());

	FillItem = settings.value("editor/fill", false).toBool();
	Alignment = settings.value("editor/align", 9).toInt();
	LineWidth = settings.value("editor/width", 1).toInt();
	SnapGrid = settings.value("editor/snap", 5).toInt();
	Tool = settings.value("editor/tool", 1).toInt();
}

//! Save settings.
void SymEditSettings::Save() const
{
	QSettings settings;

	settings.setValue("window/x", Position.x());
	settings.setValue("window/y", Position.y());
	settings.setValue("window/width", Size.width());
	settings.setValue("window/height", Size.height());

	settings.setValue("editor/fill", FillItem);
	settings.setValue("editor/align", Alignment);
	settings.setValue("editor/width", LineWidth);
	settings.setValue("editor/snap", SnapGrid);
	settings.setValue("editor/tool", Tool);
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

	Symbol.Load("U00,00;R50;U-34,-34;D34,34;U-34,34;D34,-34;");		//##
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
	\param value		Setting value.
*/
void SymEditManager::setFillItem(bool value) { Settings.FillItem = value; }
void SymEditManager::setAlignment(int value) { Settings.Alignment = value; }
void SymEditManager::setLineWidth(int value) { Settings.LineWidth = value; }
void SymEditManager::setSnapGrid(int value) { Settings.SnapGrid = value; }
void SymEditManager::setTool(int value) { Settings.Tool = value; }
//@}

//@{
//! Get setting value.
/*!
	\return				Setting value.
*/
bool SymEditManager::getFillItem() const { return Settings.FillItem; }
int SymEditManager::getAlignment() const { return Settings.Alignment; }
int SymEditManager::getLineWidth() const { return Settings.LineWidth; }
int SymEditManager::getSnapGrid() const { return Settings.SnapGrid; }
int SymEditManager::getTool() const { return Settings.Tool; }
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
	\return				Reference to item.
*/
void SymEditManager::addValueItem(int operation, QPoint point, int value, bool fill)
{
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
void SymEditManager::addPointItem(int operation, QPoint point, QPoint value, bool fill)
{
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
	Symbol.AddItem(operation, point, value, align);
}

//! Remove active item.
void SymEditManager::removeItem()
{
	Symbol.RemoveItem(Symbol.GetActiveIndex());
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
	const auto& item = Symbol.GetItem(index);
	return item.Operation;
}

//! Get item position.
/*!
	\param index		Item index.
	\return				Item position.
*/
QPoint SymEditManager::getItemPosition(int index) const
{
	const auto& item = Symbol.GetItem(index);
	if ( item.Operation == 'B' )	// normalize to upper left
		return QPoint(std::min(item.Value.x(), item.Point.x()), std::max(item.Value.y(), item.Point.y()));
	return item.Point;
}

//! Get item int value.
/*!
	\param index		Item index.
	\return				Item value.
*/
int SymEditManager::getItemValue(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Value.x();
}

//! Get item point value.
/*!
	\param index		Item index.
	\return				Item value.
*/
QPoint SymEditManager::getItemPoint(int index) const
{
	const auto& item = Symbol.GetItem(index);
	if ( item.Operation == 'B' )	// normalize to lower right
		return QPoint(std::max(item.Value.x(), item.Point.x()), std::min(item.Value.y(), item.Point.y()));
	return item.Value;
}

//! Get item text value.
/*!
	\param index		Item index.
	\return				Item value.
*/
QString SymEditManager::getItemText(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Text;
}

//
bool SymEditManager::getItemFill(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Fill;
}

//
int SymEditManager::selectItem(QPoint point) const
{
	return Symbol.SelectItem(point);
}

//
void SymEditManager::setActiveIndex(int index)
{
	Symbol.SetActiveIndex(index);
}

//
int SymEditManager::getActiveIndex() const
{
	return Symbol.GetActiveIndex();
}

//! Cut symbol to clipboard.
void SymEditManager::cutClipboard()
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
	{
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
		Symbol.Load(clipboard->text());
}


