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
	friend class SymEditManager;

public:
	SymEditSettings();

	void Load();
	void Save() const;

private:
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

	//! Save settings.
	void SaveSettings() const { Settings.Save(); }

	Q_INVOKABLE void setInitialized();

	Q_INVOKABLE void setGeometry(QPoint point, QSize size);
	Q_INVOKABLE QPoint getWindowPos() const;
	Q_INVOKABLE QSize getWindowSize() const;

	Q_INVOKABLE void setFill(bool fill);
	Q_INVOKABLE void setAlign(int align);
	Q_INVOKABLE void setSnap(int snap);
	Q_INVOKABLE void setTool(int tool);

	Q_INVOKABLE bool getFill() const;
	Q_INVOKABLE int getAlign() const;
	Q_INVOKABLE int getTool() const;
	Q_INVOKABLE int getSnap() const;

	Q_INVOKABLE QString getSymbol() const;

	Q_INVOKABLE void addItem(int operation, QPoint point, bool fill);
	Q_INVOKABLE void addText(int operation, QPoint point, QString text, int align);
	Q_INVOKABLE void removeItem(int index);

	Q_INVOKABLE int getItemCount() const;
	Q_INVOKABLE int getItemOperation(int index) const;
	Q_INVOKABLE QPoint getItemPoint(int index) const;
	Q_INVOKABLE QString getItemString(int index ) const;
	Q_INVOKABLE bool getItemFill(int index) const;

	Q_INVOKABLE int selectItem(QPoint point) const;

	Q_INVOKABLE void readClipboard();
	Q_INVOKABLE void writeClipboard() const;

private:
	bool Initialized = false;				//!< Initialization mutex.
	SymEditSymbol Symbol;					//!< Current symbol.
	SymEditSettings Settings;				//!< Editor settings.
};

#endif
