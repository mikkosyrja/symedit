#include <QStringList>

#include <math.h>

#include "symbol.h"

//
//	symbol item functions
//
//@{
//! Constructor.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item value.
	\param fill			Item area fill.
*/
SymEditSymbol::Item::Item(int operation, QPoint point, int value, bool fill)
	: Operation(operation), Point(point), Value(value, value), Fill(fill), Align(9)
{

}
SymEditSymbol::Item::Item(int operation, QPoint point, QPoint value, bool fill)
	: Operation(operation), Point(point), Value(value), Fill(fill), Align(0)
{

}
SymEditSymbol::Item::Item(int operation, QPoint point, QString value, int align)
	: Operation(operation), Point(point), Text(value), Fill(false), Align(align)
{

}
//@}

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
	Items.clear();
	QPoint position(0, 0);
	for ( const auto& string : buffer.split(';', QString::SkipEmptyParts) )
	{
		int operation = string.at(0).toLatin1();
		int comma = string.indexOf(',');
		if ( comma >= 0 )
		{
			int x = string.mid(1, comma - 1).toInt();
			int y = string.mid(comma + 1).toInt();
			if ( operation != 'U' )
				Items.push_back(Item(operation, position, QPoint(x, y), false));
			position = QPoint(x, y);
		}
		else	// single parameter
		{
			int value = string.mid(1).toInt();
			Items.push_back(Item(operation, position, value, false));
		}
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
	QPoint position(0, 0);
	for ( const auto& item : Items ) switch ( item.Operation )
	{
		case 'D':	// line
		case 'B':	// rectangle
		{
			if ( item.Point != position )
				appendvalue(buffer.append('U'), item.Point, 2);
			appendvalue(buffer.append(item.Operation), item.Value, 2);
			position = item.Value;
			break;
		}
		case 'R':
		{
			if ( item.Point != position )
				appendvalue(buffer.append('U'), item.Point, 2);
			appendvalue(buffer.append(item.Operation), item.Value, 1);
			position = item.Point;
			break;
		}
	}
	if ( !buffer.isEmpty() && buffer.back() == ';' )
		buffer.chop(1);

	return buffer;
}

//! Clear symbol.
void SymEditSymbol::Clear()
{
	Items.clear();
}

//@{
//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param value		Item value.
	\param fill			Item area fill.
	\return				Reference to item.
*/
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, int value, bool fill)
{
	Item item(operation, point, value, fill);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, QPoint value, bool fill)
{
	Item item(operation, point, value, fill);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, QString value, int align)
{
	Item item(operation, point, value, align);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}
//@}

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
			case 'B':	// rectangle
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
void SymEditSymbol::SetActiveIndex(int index)
{
	ActiveIndex = index;
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

