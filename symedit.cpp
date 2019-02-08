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

//
void SymEditManager::addItem(int operation, QPoint point)
{

}

//
void SymEditManager::removeItem(int index)
{

}


//
int SymEditManager::getItemCount() const
{
	return 2;
}

//
int SymEditManager::getItemOperation(int index) const
{
	if ( index == 0 )
		return 'U';
	else
		return 'R';
}

//
QPoint SymEditManager::getItemPoint(int index) const
{
	if ( index == 0 )
		return QPoint(0, 0);
	else
		return QPoint(30, 30);
}

//
QString SymEditManager::getItemString(int index) const
{
	return "T3";
}

//
bool SymEditManager::getItemFill(int index) const
{
	return false;
}
