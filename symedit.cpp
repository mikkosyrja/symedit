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
	\param fill			Item area fill.
	\return				Reference to item.
*/
void SymEditManager::addItem(int operation, QPoint point, bool fill)
{
	Symbol.AddItem(operation, point, fill);
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param text			Item text string.
	\param align		Item text alignment.
	\return				Reference to item.
*/
void SymEditManager::addText(int operation, QPoint point, QString text, int align)
{
	Symbol.AddItem(operation, point, text, align);
}

//! Remove item.
/*!
	\param index		Item index.
*/
void SymEditManager::removeItem(int index)
{
	Symbol.RemoveItem(index);
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
QPoint SymEditManager::getItemPoint(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Point;
}

//! Get item string.
/*!
	\param index		Item index.
	\return				Item string.
*/
QString SymEditManager::getItemString(int index) const
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
	return -1;	//##
}

//! Read symbol from clipboard.
void SymEditManager::readClipboard()
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
		Symbol.Load(clipboard->text());
}

//! Write symbol to clipboard.
void SymEditManager::writeClipboard() const
{
	if ( QClipboard* clipboard = QGuiApplication::clipboard() )
		clipboard->setText(getSymbol());
}

