#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>

#include <QPoint>
#include <QString>

//! Symbol class.
class SymEditSymbol
{
public:
	SymEditSymbol();

	class Item								//!< Symbol item.
	{
	public:
		Item(int operation, QPoint point, int value, int fill);
		Item(int operation, QPoint point, QPoint value, int fill);
		Item(int operation, QPoint point, QString value, int align);

		int Operation;						//!< Item operation.
		QPoint Point;						//!< Item coordinates.
		QPoint Value;						//!< Item value.
		QString Text;						//!< Text string.
		int Fill;							//!< Fill area.
		int Align;							//!< Text alignment.
	};

	void Load(const QString& buffer);
	QString& Save(QString& buffer) const;
	void Clear();

	Item& AddItem(int operation, QPoint point, int value, int fill);
	Item& AddItem(int operation, QPoint point, QPoint end, int fill);
	Item& AddItem(int operation, QPoint point, QString text, int align);
	bool RemoveItem(int index);

	int SelectItem(QPoint point) const;
	void SetActiveIndex(int index);
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
