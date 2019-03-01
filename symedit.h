#ifndef SYMEDIT_H
#define SYMEDIT_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QTranslator>

#include <deque>

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

	std::map<QString, int> IntValues;		//!< Integer setting values.
	std::map<QString, QString> TextValues;	//!< String setting values.
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

	Q_INVOKABLE void setIntSetting(QString name, int value);
	Q_INVOKABLE int getIntSetting(QString name) const;
	Q_INVOKABLE void setTextSetting(QString name, QString value);
	Q_INVOKABLE QString getTextSetting(QString name) const;

	Q_INVOKABLE QString getSymbol() const;

	Q_INVOKABLE bool addValueItem(int operation, QPoint point, int value, int fill);
	Q_INVOKABLE bool addPointItem(int operation, QPoint point, QPoint value, int fill);
	Q_INVOKABLE bool addTextItem(int operation, QPoint point, QString value, int align);
	Q_INVOKABLE bool removeItem();

	Q_INVOKABLE int getItemCount() const;
	Q_INVOKABLE int getItemOperation(int index) const;
	Q_INVOKABLE QPoint getItemPosition(int index) const;
	Q_INVOKABLE int getItemValue(int index) const;
	Q_INVOKABLE QPoint getItemPoint(int index) const;
	Q_INVOKABLE QString getItemText(int index ) const;
	Q_INVOKABLE int getItemFill(int index) const;
	Q_INVOKABLE int getItemAlign(int index) const;

	Q_INVOKABLE int selectItem(QPoint point) const;
	Q_INVOKABLE void setActiveIndex(int index);
	Q_INVOKABLE int getActiveIndex() const;

	Q_INVOKABLE void cutClipboard();
	Q_INVOKABLE void copyClipboard() const;
	Q_INVOKABLE void pasteClipboard();

	Q_INVOKABLE void rotateSymbol(int dir);
	Q_INVOKABLE bool raiseItem(int dir);

	Q_INVOKABLE bool undo(bool undo);

private:
	void undosave();

	bool Initialized = false;				//!< Initialization mutex.
	SymEditSymbol Symbol;					//!< Current symbol.
	SymEditSettings Settings;				//!< Editor settings.

	std::deque<QString> UndoStack;			//!< Undo stack.
	std::deque<QString> RedoStack;			//!< Redo stack.

	QTranslator BackupTranslator;			//!< UI backup translator.
	QTranslator LocaleTranslator;			//!< UI locale translator.
};
#endif
