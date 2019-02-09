#include <QStringList>

#include "symbol.h"

//
//	symbol item functions
//
//! Constructor.
/*!
	\param operation	Item operation.
	\param point		Item position.
*/
SymEditSymbol::Item::Item(int operation, QPoint point)
	: Operation(operation), Point(point), Fill(false)
{

}

//
//	symbol functions
//
//! Constructor.
SymEditSymbol::SymEditSymbol() : ActiveIndex(-1)
{

}

//! Load symbol from string.
/*!
	\param buffer		String buffer.
*/
void SymEditSymbol::Load(const QString& buffer)
{
	QStringList list = buffer.split(';', QString::SkipEmptyParts);
	for ( const auto& string : list )
	{
		int operation = string.at(0).toLatin1();
		int x = string.mid(1).toInt();
		int y = x;
		int comma = string.indexOf(',');
		if ( comma >= 0 )
			y = string.mid(comma + 1).toInt();

		Item item(operation, QPoint(x, y));
		Items.push_back(item);
	}
}

//! Save symbol to string.
/*!
	\param buffer		String buffer.
*/
void SymEditSymbol::Save(QString& buffer) const
{
	buffer.clear();
	for ( const auto& item : Items )
	{
		//##
	}
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param fill			Item area fill.
	\return				Reference to item.
*/
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, bool fill)
{
	Item item(operation, point);
	item.Fill = fill;
	Items.push_back(item);
	return Items.back();
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param text			Item text string.
	\param align		Item text alignment.
	\return				Reference to item.
*/
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, QString text, int align)
{
	Item item(operation, point);
	item.Text = text;
	item.Align = align;
	Items.push_back(item);
	return Items.back();
}

//! Remove item.
/*!
	\param index		Item index.
*/
void SymEditSymbol::RemoveItem(int index)
{
	if ( static_cast<size_t>(index) < Items.size() )
		Items.erase(Items.begin() + index);
}

//
int SymEditSymbol::SelectItem(QPoint point) const
{
	ActiveIndex = -1;	//##
	return ActiveIndex;
}

//! Get item count.
/*!
	\return				Item count.
*/
int SymEditSymbol::GetItemCount() const
{
	return static_cast<int>(Items.size());
}

//
const SymEditSymbol::Item& SymEditSymbol::GetItem(int index) const
{
	return Items.at(static_cast<size_t>(index));
}

