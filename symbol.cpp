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
SymEditSymbol::Item::Item(int operation, QPoint point, int value, int fill)
	: Operation(operation), Point(point), Value(value, value), Fill(fill), Align(9)
{

}
SymEditSymbol::Item::Item(int operation, QPoint point, QPoint value, int fill)
	: Operation(operation), Point(point), Value(value), Fill(fill), Align(0)
{

}
SymEditSymbol::Item::Item(int operation, QPoint point, QString value, int align)
	: Operation(operation), Point(point), Text(value), Fill(0), Align(align)
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
		case 'R':	// circle
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
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, int value, int fill)
{
	Item item(operation, point, value, fill);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}
SymEditSymbol::Item& SymEditSymbol::AddItem(int operation, QPoint point, QPoint value, int fill)
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
	\return				True for success.
*/
bool SymEditSymbol::RemoveItem(int index)
{
	if ( static_cast<size_t>(index) < Items.size() )
	{
		Items.erase(Items.begin() + index);
		ActiveIndex = index - 1;
		return true;
	}
	return false;
}

//! Select item nearest to point.
/*!
	\param point		Point coordinates.
	\return				Nearest item index.
*/
int SymEditSymbol::SelectItem(QPoint point) const
{
	ActiveIndex = -1;
	int index = 0;
	double minimum = 100.0;

	auto difference = [](const QPoint& start, const QPoint& end) { return QPoint(end.x() - start.x(), end.y() - start.y()); };
	auto length = [](const QPoint& point) { return sqrt(point.x() * point.x() + point.y() * point.y()); };
	auto scalar = [](const QPoint& start, const QPoint& end) { return static_cast<double>(start.x() * end.x() + start.y() * end.y()); };
	auto cross = [](const QPoint& start, const QPoint& end) { return static_cast<double>(start.x() * end.y() - start.y() * end.x()); };
	auto projection = [&](const QPoint& point, const QPoint& start, const QPoint& end)
	{
		QPoint line = difference(start, end);
		return scalar(difference(start, point), line) / length(line);
	};
	auto check = [&](double distance)
	{
		if ( ActiveIndex < 0 || distance < minimum )
		{
			ActiveIndex = index;
			minimum = distance;
		}
	};

	auto distance = [&](const QPoint& point, const QPoint& start, const QPoint& end)
	{
		QPoint line = difference(start, end);
		double len = length(line), a = projection(point, start, end);
		if ( a > 0.0 && a < len )
			check(fabs(cross(difference(start, point), line) / len));
		check(length(difference(point, start)));
		check(length(difference(point, end)));
	};

	for ( const auto& item : Items )
	{
		switch ( item.Operation )
		{
			case 'D':	// line
			{
				distance(point, item.Point, item.Value);
				break;
			}
			case 'B':	// rectangle
			{
				distance(point, item.Point, QPoint(item.Point.x(), item.Value.y()));
				distance(point, QPoint(item.Point.x(), item.Value.y()), item.Value);
				distance(point, item.Value, QPoint(item.Value.x(), item.Point.y()));
				distance(point, QPoint(item.Value.x(), item.Point.y()), item.Point);
				break;
			}
			case 'R':	// circle
			{
				check(fabs(length(difference(point, item.Point)) - item.Value.x()));
				break;
			}
		}
		++index;
	}
	return ActiveIndex;
}

//! Set active item index.
/*!
	\param index		Active item index.
*/
void SymEditSymbol::SetActiveIndex(int index)
{
	ActiveIndex = index;
}

//! Get active item index.
/*!
	\return				Active item index.
*/
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

//! Rotate symbol.
/*!
	\param dir			Positive value rotates right, negative left
*/
void SymEditSymbol::RotateSymbol(int dir)
{
	auto rotate = [](QPoint& point, int dir)
	{
		double length = sqrt(point.x() * point.x() + point.y() * point.y());
		double angle = atan2(point.y(), point.x());
		angle += (dir > 0 ? -M_PI / 2.0 : M_PI / 2.0);
		double x = cos(angle) * length, y = sin(angle) * length;
		point.setX(static_cast<int>(x + (x > 0.0 ? 0.5 : -0.5)));
		point.setY(static_cast<int>(y + (y > 0.0 ? 0.5 : -0.5)));
	};

	for ( auto& item : Items )
	{
		rotate(item.Point, dir);
		if ( item.Operation != 'R' )
			rotate(item.Value, dir);
	}
}
