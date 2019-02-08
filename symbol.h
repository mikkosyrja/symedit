#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <QPoint>

class SymEditSymbol
{
public:
	SymEditSymbol();

	class Item								//!< Symbol item.
	{
		Item();

		int Operation;						//!< Item operation.
		QPoint Point;						//!< Item coordinates.
		bool Fill;							//!< Fill area.
	};

	void Load(const QString& string);
	void Save(QString& string) const;

private:
	std::vector<Item> Items;				//!< Symbol items.
};

#endif
