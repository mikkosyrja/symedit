#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>

#include <QPoint>
#include <QString>
#include <QObject>

namespace Operation							//!< Item operation namespace.
{
	Q_NAMESPACE
	enum Type								//!< Item operation type.
	{
		None = 0,							//!< No operation.
		Line = 1,							//!< Straight line with two points.
		Rectangle = 2,						//!< Rectangle with two corners.
		Circle = 3,							//!< Circle with center and radius.
		Text = 4,							//!< Text with single position point.
		Arc = 5								//!< Semicircle with two endpoints.
	};
	Q_ENUM_NS(Type)
}

//! Symbol class.
class SymEditSymbol
{
public:
	SymEditSymbol();

	class Item								//!< Symbol item.
	{
	public:
		Item();
		Item(Operation::Type operation, QPoint point, int value, int color, int fill);
		Item(Operation::Type operation, QPoint point, QPoint value, int color, int fill);
		Item(Operation::Type operation, QPoint point, QString value, int color, int align);

		Operation::Type Operation;			//!< Item operation.
		QPoint Point;						//!< Item coordinates.
		QPoint Value;						//!< Item value.
		QString Text;						//!< Text string.
		int Color;							//!< Color index.
		int Fill;							//!< Fill area.
		int Align;							//!< Text alignment.
	};

	void Load(const QString& buffer);
	QString& Save(QString& buffer) const;
	void Clear();

	Item& AddItem(Operation::Type operation, QPoint point, int value, int color, int fill);
	Item& AddItem(Operation::Type operation, QPoint point, QPoint end, int color, int fill);
	Item& AddItem(Operation::Type operation, QPoint point, QString text, int color, int align);
	bool RemoveItem(int index);

	int SelectItem(QPoint point) const;
	bool SetActiveIndex(int index);
	int GetActiveIndex() const;

	int GetItemCount() const;
	const Item& GetItem(int index) const;

	void RotateSymbol(int dir);
	bool RaiseItem(int dir);

private:
	std::vector<Item> Items;				//!< Symbol items.

	mutable int ActiveIndex;				//!< Active item index.
};

#endif
