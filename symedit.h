#ifndef SYMEDIT_H
#define SYMEDIT_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>

#include "symbol.h"

//! Settings class.
class SymEditSettings
{
public:
	SymEditSettings();

	QPoint Position;						//!< Window position.
	QSize Size;								//!< Window size.

	bool Fill;								//!< Fill object.
	int Align;								//!< Text alignment.
	int Snap;								//!< Snap granularity.
	int Tool;								//!< Current tool.
};

//! Manager class.
class SymEditManager : public QObject
{
	Q_OBJECT

public:
	explicit SymEditManager(QObject* parent = nullptr);

	Q_INVOKABLE void setGeometry(QPoint point, QSize size);
	Q_INVOKABLE QPoint getPosition() const;
	Q_INVOKABLE QSize getSize() const;

	Q_INVOKABLE void setFill(bool fill);
	Q_INVOKABLE void setAlign(int align);
	Q_INVOKABLE void setSnap(int snap);
	Q_INVOKABLE void setTool(int tool);

	Q_INVOKABLE bool getFill() const;
	Q_INVOKABLE int getAlign() const;
	Q_INVOKABLE int getTool() const;
	Q_INVOKABLE int getSnap() const;

	Q_INVOKABLE void addItem(int operation, QPoint point);
	Q_INVOKABLE void removeItem(int index);

	Q_INVOKABLE int getItemCount() const;
	Q_INVOKABLE int getItemOperation(int index) const;
	Q_INVOKABLE QPoint getItemPoint(int index) const;
	Q_INVOKABLE QString getItemString(int index ) const;
	Q_INVOKABLE bool getItemFill(int index) const;

	void LoadSettings();
	void SaveSettings();

private:
	SymEditSymbol Symbol;					//!< Current symbol.
	SymEditSettings Settings;				//!< Editor settings.
};

#endif
