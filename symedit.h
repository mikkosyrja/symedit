#ifndef SYMEDIT_H
#define SYMEDIT_H

#include <QObject>
#include <QString>
#include <QClipboard>

//! Manager class.
class SymEdit : public QObject
{
	Q_OBJECT

public:
	explicit SymEdit(QObject* parent = nullptr);

	Q_INVOKABLE void setFill(bool fill);
	Q_INVOKABLE bool getFill() const;
	Q_INVOKABLE void setSnap(int snap);
	Q_INVOKABLE int getSnap() const;
	Q_INVOKABLE void setAlign(int align);
	Q_INVOKABLE int getAlign() const;

private:
	QClipboard* clipboard;					//!< System clipboard.
};

#endif
