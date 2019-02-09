#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>

#include <QPoint>
#include <QString>

class SymEditSymbol
{
public:
	SymEditSymbol();

	class Item								//!< Symbol item.
	{
	public:
		Item(int operation, QPoint point);

		int Operation;						//!< Item operation.
		QPoint Point;						//!< Item coordinates.
		bool Fill;							//!< Fill area.
		int Align;							//!< Text alignment.
		QString Text;						//!< Text string.
	};

	void Load(const QString& buffer);
	void Save(QString& buffer) const;

	Item& AddItem(int operation, QPoint point, bool fill);
	Item& AddItem(int operation, QPoint point, QString text, int align);
	void RemoveItem(int index);
	int SelectItem(QPoint point) const;

	int GetItemCount() const;
	const Item& GetItem(int index) const;

private:
	std::vector<Item> Items;				//!< Symbol items.

	mutable int ActiveIndex;				//!< Active item index.
};

#endif
