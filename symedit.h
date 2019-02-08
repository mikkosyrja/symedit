#ifndef SYMEDIT_H
#define SYMEDIT_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>

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

	Q_INVOKABLE void setPosition(QPoint point);
	Q_INVOKABLE void setSize(QSize size);

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

	void LoadSettings();
	void SaveSettings();

private:
	SymEditSettings Settings;				//!< Editor settings.
};

#endif
