#include <QGuiApplication>
#include <QSettings>

#include "symedit.h"

//
//	settings functions
//
//! Constructor.
SymEditSettings::SymEditSettings() : Fill(false), Align(9), Snap(5), Tool(1)
{

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
	LoadSettings();

	Symbol.Load("U00,00;R50;U-35,-35;D35,35;U-35,35;D35,-35;");
}

//! Set window geometry.
/*!
	\param point		Window position.
	\param size			Window size.
*/
void SymEditManager::setGeometry(QPoint point, QSize size)
{
	Settings.Position = point;
	Settings.Size = size;
}

//! Get window position.
/*!
	\return				Window position.
*/
QPoint SymEditManager::getPosition() const
{
	return Settings.Position;
}

//! Get window size.
/*!
	\return				Window size.
*/
QSize SymEditManager::getSize() const
{
	return Settings.Size;
}

//@{
//! Set setting value.
/*!
	\param value		Setting value.
*/
void SymEditManager::setFill(bool value) { Settings.Fill = value; }
void SymEditManager::setAlign(int value) { Settings.Align = value; }
void SymEditManager::setSnap(int value) { Settings.Snap = value; }
void SymEditManager::setTool(int value) { Settings.Tool = value; }
//@}

//@{
//! Get setting value.
/*!
	\return				Setting value.
*/
bool SymEditManager::getFill() const { return Settings.Fill; }
int SymEditManager::getAlign() const { return Settings.Align; }
int SymEditManager::getSnap() const { return Settings.Snap; }
int SymEditManager::getTool() const { return Settings.Tool; }
//@}

//! Load settings.
void SymEditManager::LoadSettings()
{
	QSettings settings;

	Settings.Position.setX(settings.value("window/x", 100).toInt());
	Settings.Position.setY(settings.value("window/y", 100).toInt());
	Settings.Size.setWidth(settings.value("window/width", 500).toInt());
	Settings.Size.setHeight(settings.value("window/height", 500).toInt());

	Settings.Fill = settings.value("editor/fill", false).toBool();
	Settings.Align = settings.value("editor/align", 9).toInt();
	Settings.Snap = settings.value("editor/snap", 5).toInt();
	Settings.Tool = settings.value("editor/tool", 1).toInt();
}

//! Save settings.
void SymEditManager::SaveSettings()
{
	QSettings settings;

	settings.setValue("window/x", Settings.Position.x());
	settings.setValue("window/y", Settings.Position.y());
	settings.setValue("window/width", Settings.Size.width());
	settings.setValue("window/height", Settings.Size.height());

	settings.setValue("editor/fill", Settings.Fill);
	settings.setValue("editor/align", Settings.Align);
	settings.setValue("editor/snap", Settings.Snap);
	settings.setValue("editor/tool", Settings.Tool);
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

//
int SymEditManager::getItemOperation(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Operation;
}

//
QPoint SymEditManager::getItemPoint(int index) const
{
	const auto& item = Symbol.GetItem(index);
	return item.Point;
}

//
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

int SymEditManager::selectItem(QPoint point) const
{
	return -1;	//##
}

