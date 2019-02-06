#include <QGuiApplication>

#include "symedit.h"

//! Constructor.
/*!
	\param parent		//!< Optional parent.
*/
SymEdit::SymEdit(QObject* parent) : QObject(parent)
{
	clipboard = QGuiApplication::clipboard();
}

//
void SymEdit::setFill(bool fill)
{
	//##
}

//
bool SymEdit::getFill() const
{
	return true;	//##
}

//
void SymEdit::setSnap(int snap)
{
	//##
}

//
int SymEdit::getSnap() const
{
	return 5;	//##
}

//
void SymEdit::setAlign(int align)
{
	//##
}

//
int SymEdit::getAlign() const
{
	return 9;	//##
}
