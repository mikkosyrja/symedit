#include <QStringList>

#include <math.h>

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
	: Operation(operation), Point(point), Fill(false), Align(9)
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
		int x, y, comma = string.indexOf(',');
		if ( comma >= 0 )
		{
			x = string.mid(1, comma - 1).toInt();
			y = string.mid(comma + 1).toInt();
		}
		else	// single parameter
			x = y = string.mid(1).toInt();
		Item item(operation, QPoint(x, y));
		Items.push_back(item);
	}
	ActiveIndex = static_cast<int>(Items.size()) - 1;
}

//! Save symbol to string.
/*!
	\param buffer		String buffer.
	\return				Reference to buffer.
*/
QString& SymEditSymbol::Save(QString& buffer) const
{
	auto appendvalue = [](QString& buffer, const QPoint& point, int count)
	{
		QString value;
		buffer.append(value.setNum(point.x()));
		if ( count > 1 )
			buffer.append(',').append(value.setNum(point.y()));
		buffer.append(';');
	};

	buffer.clear();
	for ( const auto& item : Items ) switch ( item.Operation )
	{
		case 'D':	appendvalue(buffer.append('D'), item.Point, 2); break;
		case 'U':	appendvalue(buffer.append('U'), item.Point, 2); break;
		case 'R':	appendvalue(buffer.append('R'), item.Point, 1); break;
	}
	if ( !buffer.isEmpty() && buffer.back() == ';' )
		buffer.chop(1);
	return buffer;
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
	ActiveIndex = static_cast<int>(Items.size());
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
	ActiveIndex = static_cast<int>(Items.size());
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
	{
		Items.erase(Items.begin() + index);
		ActiveIndex = index - 1;
	}
}

//
int SymEditSymbol::SelectItem(QPoint point) const
{
	ActiveIndex = -1;
	int index = 0;
	QPoint previous(0, 0);
	double minimum = 100.0;
	for ( const auto& item : Items )
	{
		switch ( item.Operation )
		{
			case 'D':	// line
			{
				//##
				break;
			}
			case 'R':	// circle
			{
				double dx = point.x() - previous.x();
				double dy = point.y() - previous.y();
				double distance = sqrt(dx * dx + dy * dy);
				distance = abs(distance - item.Point.x());
				if ( ActiveIndex < 0 || distance < minimum )
				{
					ActiveIndex = index;
					minimum = distance;
				}
				break;
			}
		}
		++index;
	}
	return static_cast<int>(ActiveIndex);
}

//
int SymEditSymbol::GetActiveIndex() const
{
	return static_cast<int>(ActiveIndex);
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

