#include <QStringList>

#include <math.h>

#include "symbol.h"

const double ConstPi = 3.14159265358979323846;	//!< Constant for PI.
const double ConstPi2 = ConstPi / 2.0;			//!< Constant for PI / 2.

namespace Operation
{
	Q_NAMESPACE
}

//
//	symbol item functions
//
const SymEditSymbol::Item gDefaultItem;		//!< Empty default item.

//! Constructor.
SymEditSymbol::Item::Item() : Operation(Operation::None), Fill(0), Align(9), Unit(0)
{

}

//! Constructor.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param end			End position.
	\param value		Item value.
	\param color		Item color index.
	\param fill			Item area fill.
*/
SymEditSymbol::Item::Item(Operation::Type operation, QPoint point, QPoint end, int value, int color, int fill)
	: Operation(operation), Point(point), End(end), Size(0.0), Value(value), Color(color), Fill(fill), Align(0), Unit(0)
{

}

//! Constructor.
/*!
	\param operation	Item operation.
	\param point		Item position.
	\param end			End position.
	\param text			Text string.
	\param size 		Text size.
	\param unit 		Size unit.
	\param color		Item color index.
	\param align		Text alignment.
*/
SymEditSymbol::Item::Item(Operation::Type operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align)
	: Operation(operation), Point(point), End(end), Text(text), Size(size), Value(0), Color(color), Fill(0), Align(align), Unit(unit)
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
	Items.clear();
	QPoint position(0, 0);
	double size = 0.0;
	int color = 1, fill = 0, align = 9, angle = 0, unit = 0;
	for ( const auto& string : buffer.split(';', QString::SkipEmptyParts) )
	{
		int type = string.at(0).toLatin1();
		int comma = string.indexOf(',');
		if ( comma >= 0 )
		{
			int x = string.mid(1, comma - 1).toInt();
			int y = string.mid(comma + 1).toInt();
			if ( type == 'D' )
				Items.push_back(Item(Operation::Line, position, QPoint(x, y), 0, color, fill));
			else if ( type == 'B' )
				Items.push_back(Item(Operation::Rectangle, position, QPoint(x, y), 0, color, fill));
//			else if ( type == 'H' )
//				Items.push_back(Item(Operation::Arc, position, QPoint(x, y), color, fill));
			position = QPoint(x, y);
		}
		else	// single parameter
		{
			int value = string.mid(1).toInt();
			if ( type == 'C' )
				color = value;
			else if ( type == 'F' )
				fill = value;
			else if ( type == 'J' )
				align = value;
			else if ( type == 'S' || type == 'P' )
			{
				size = string.mid(1).toDouble();
				unit = (type == 'P' ? 2 : (size < 0.0 ? 1 : 0));
				size = fabs(size) * (type == 'P' ? 0.1 : 1.0);
			}
			else if ( type == 'G' )
				angle = value;
			else if ( type == 'R' )
				Items.push_back(Item(Operation::Circle, position, position, value, color, fill));
			else if ( type == '!' || type == '$' || type == '#' )
			{
				QPoint end = position;
				if ( angle )
				{
					double radian = angle / 200.0 * ConstPi;
					end = QPoint(static_cast<int>(cos(radian) * 100.0), static_cast<int>(sin(radian) * 100.0));
				}
				Items.push_back(Item(Operation::Text, position, end, type == '!' ? string.mid(1) : string, size, unit, color, align));
			}
		}
	}
	ActiveIndex = static_cast<int>(Items.size()) - 1;
}

//! Save symbol to string.
/*!
	\param buffer		String buffer.
	\param rich			Rich text with layout.
	\return				Reference to buffer.
*/
QString& SymEditSymbol::Save(QString& buffer, bool rich) const
{
	auto appendpoint = [](QString& buffer, const QPoint& point, int count)
	{
		QString value;
		buffer.append(value.setNum(point.x()));
		if ( count > 1 )
			buffer.append(',').append(value.setNum(point.y()));
		buffer.append(';');
	};
	auto appendoption = [](QChar option, QString& buffer, int index)
	{
		QString value;
		buffer.append(option).append(value.setNum(index)).append(';');
		return index;
	};

	buffer.clear();
	QPoint position(0, 0);
	double size = 0.0;
	int index = 0, color = 1, fill = 0, align = 9, angle = 0, unit = 0;
	for ( const auto& item : Items )
	{
		if ( rich && index == ActiveIndex )
			buffer.append("<b>");
		switch ( item.Operation )
		{
			case Operation::Line:
			case Operation::Rectangle:
			{
				if ( item.Color != color )
					color = appendoption('C', buffer, item.Color);
				if ( item.Fill != fill )
					fill = appendoption('F', buffer, item.Fill);
				if ( item.Point != position )
					appendpoint(buffer.append('U'), item.Point, 2);
				appendpoint(buffer.append(item.Operation == Operation::Line ? 'D' : 'B'), item.End, 2);
				position = item.End;
				break;
			}
			case Operation::Circle:
			{
				if ( item.Color != color )
					color = appendoption('C', buffer, item.Color);
				if ( item.Fill != fill )
					fill = appendoption('F', buffer, item.Fill);
				if ( item.Point != position )
					appendpoint(buffer.append('U'), item.Point, 2);
				appendoption('R', buffer, item.Value);
				position = item.Point;
				break;
			}
			case Operation::Text:
			{
				int temp = 0;
				if ( item.Point.y() != item.End.y() || item.Point.x() != item.End.x() )
					temp = static_cast<int>(atan2(item.End.y() - item.Point.y(), item.End.x() - item.Point.x()) / ConstPi * 200.0);
				if ( temp != angle )
					angle = appendoption('G', buffer, temp);
				if ( item.Color != color )
					color = appendoption('C', buffer, item.Color);
				if ( item.Align != align )
					align = appendoption('J', buffer, item.Align);
				if ( item.Size != size || item.Unit != unit )
				{
					QString value;
					unit = item.Unit;
					size = item.Size * (unit == 2 ? 10.0 : 1.0);
					buffer.append(unit == 2 ? 'P' : 'S').append(value.setNum(size * (unit == 1 ? -1.0 : 1.0))).append(';');
				}
				if ( item.Point != position )
					appendpoint(buffer.append('U'), item.Point, 2);
				if ( item.Text.front() != '$' && item.Text.front() != '#' )
					buffer.append('!');		// constant text
				buffer.append(item.Text).append(';');
				break;
			}
			case Operation::Arc:
			{
				if ( item.Color != color )
					color = appendoption('C', buffer, item.Color);
				if ( item.Fill != fill )
					fill = appendoption('F', buffer, item.Fill);
				if ( item.Point != position )
					appendpoint(buffer.append('U'), item.Point, 2);
				appendoption('H', buffer, item.Value);
				position = item.Point;
				break;
			}
			default:		assert(0);
		}
		if ( rich && index == ActiveIndex )
			buffer.append("</b>");
		++index;
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

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Start position.
	\param end			End position.
	\param value		Item value.
	\param color		Item color index.
	\param fill			Item area fill.
	\return				Reference to item.
*/
SymEditSymbol::Item& SymEditSymbol::AddItem(Operation::Type operation, QPoint point, QPoint end, int value, int color, int fill)
{
	Item item(operation, point, end, value, color, fill);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}

//! Add symbol item.
/*!
	\param operation	Item operation.
	\param point		Start position.
	\param end			End position.
	\param text			Text string.
	\param size 		Text size.
	\param unit 		Size unit.
	\param color		Item color index.
	\param align		Text alignment.
	\return				Reference to item.
*/
SymEditSymbol::Item& SymEditSymbol::AddItem(Operation::Type operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align)
{
	Item item(operation, point, end, text, size, unit, color, align);
	ActiveIndex = static_cast<int>(Items.size());
	Items.push_back(item);
	return Items.back();
}

//! Remove item.
/*!
	\param index		Item index.
	\return				True for success.

	Activates previous or first item.
*/
bool SymEditSymbol::RemoveItem(int index)
{
	if ( static_cast<size_t>(index) < Items.size() )
	{
		Items.erase(Items.begin() + index);
		ActiveIndex = (index == 0 && !Items.empty() ? 0 : index - 1);
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
			case Operation::Line:
			{
				distance(point, item.Point, item.End);
				break;
			}
			case Operation::Rectangle:
			{
				distance(point, item.Point, QPoint(item.Point.x(), item.End.y()));
				distance(point, QPoint(item.Point.x(), item.End.y()), item.End);
				distance(point, item.End, QPoint(item.End.x(), item.Point.y()));
				distance(point, QPoint(item.End.x(), item.Point.y()), item.Point);
				break;
			}
			case Operation::Circle:
			{
				check(fabs(length(difference(point, item.Point)) - item.Value));
				break;
			}
			case Operation::Text:
			{
				check(fabs(length(difference(point, item.Point))));
				break;
			}
			case Operation::Arc:
			{
				//##
				break;
			}
			default:		assert(0);
		}
		++index;
	}
	return ActiveIndex;
}

//! Set active item index.
/*!
	\param index		Active item index or -1 for deactivation.
	\return				True for success.
*/
bool SymEditSymbol::SetActiveIndex(int index)
{
	if ( index >= -1 && index < static_cast<int>(Items.size()) )
	{
		ActiveIndex = index;
		return true;
	}
	return false;
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

//! Get item from index.
/*!
	\param index		Item index.
	\return				Item from index.
*/
const SymEditSymbol::Item& SymEditSymbol::GetItem(int index) const
{
	if ( index >= 0 && index < static_cast<int>(Items.size()) )
		return Items.at(static_cast<size_t>(index));
	return gDefaultItem;
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
		angle += (dir > 0 ? -ConstPi2 : ConstPi2);
		double x = cos(angle) * length, y = sin(angle) * length;
		point.setX(static_cast<int>(x + (x > 0.0 ? 0.5 : -0.5)));
		point.setY(static_cast<int>(y + (y > 0.0 ? 0.5 : -0.5)));
	};

	for ( auto& item : Items )
	{
		rotate(item.Point, dir);
		if ( item.Operation == Operation::Line || item.Operation == Operation::Rectangle )
			rotate(item.End, dir);
	}
}

//! Raise or lower item.
/*!
	\param dir			Positive value raises, negative lowers.
	\return				True for success.
*/
bool SymEditSymbol::RaiseItem(int dir)
{
	if ( !Items.empty() )
	{
		size_t index = static_cast<size_t>(ActiveIndex);
		if ( dir > 0 && index < Items.size() - 1 )	// raise
		{
			std::swap(Items[index], Items[index + 1]);
			++ActiveIndex;
			return true;
		}
		if ( dir < 0 && index > 0 )		// lower
		{
			std::swap(Items[index - 1], Items[index]);
			--ActiveIndex;
			return true;
		}
	}
	return false;
}
