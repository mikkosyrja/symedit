#ifndef SYMEDIT_H
#define SYMEDIT_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QTranslator>
#include <QUrl>

#include <deque>

#include "symbol.hpp"

//! Settings class.
class SymEditSettings
{
    friend class SymEditManager;

public:
    /// @brief Constructor.
    SymEditSettings();

    /// @brief Load settings.
    void Load();

    /// @brief Save settings.
    void Save() const;

private:
    QPoint Position;                        ///< Window position.
    QSize Size;                             ///< Window size.

    std::map<QString, int> IntValues;       ///< Integer setting values.
    std::map<QString, double> RealValues;   ///< Real setting values.
    std::map<QString, QString> TextValues;  ///< String setting values.
};

//! Manager class.
class SymEditManager : public QObject
{
    Q_OBJECT

public:
    /// @brief Constructor.
    /// @param parent Optional parent.
    explicit SymEditManager(QObject* parent = nullptr);

    /// @brief Constructor.
    /// @param filename Symbol file name from command line.
    /// @param symbol Symbol string from command line.
    explicit SymEditManager(const QString& filename, const QString& symbol);

    //! Save settings.
    void SaveSettings() const { Settings.Save(); }

    /// @brief Set window initialized.
    Q_INVOKABLE void setInitialized();

    /// @brief Set window geometry.
    /// @param point Window position.
    /// @param size Window size.
    Q_INVOKABLE void setGeometry(QPoint point, QSize size);

    /// @brief Get window position.
    /// @return Window position.
    Q_INVOKABLE QPoint getWindowPos() const;

    /// @brief Get window size.
    /// @return Window size.
    Q_INVOKABLE QSize getWindowSize() const;

    /// @brief Set setting value.
    /// @param name Setting name.
    /// @param value Setting value.
    /// @{
    Q_INVOKABLE void setIntSetting(QString name, int value);
    Q_INVOKABLE void setRealSetting(QString name, double value);
    Q_INVOKABLE void setTextSetting(QString name, QString value);
    /// @}

    /// @brief Get setting value.
    /// @param name Setting name.
    /// @return Setting value.
    /// @{
    Q_INVOKABLE int getIntSetting(QString name) const;
    Q_INVOKABLE double getRealSetting(QString name) const;
    Q_INVOKABLE QString getTextSetting(QString name) const;
    /// @}

    /// @brief Get symbol as string.
    /// @param rich True for rich text with layout.
    /// @return Symbol as string.
    Q_INVOKABLE QString getSymbol(bool rich) const;

    /// @brief Add point item.
    /// @param operation Item operation.
    /// @param point Point position.
    /// @param value Item value.
    /// @param color Color index.
    /// @param fill Item area fill.
    /// @return True for success.
    Q_INVOKABLE bool addPointItem(int operation, QPoint point, int value, int color, int fill);

    /// @brief Add symbol item.
    /// @param operation Item operation.
    /// @param point Start position.
    /// @param end End position.
    /// @param value Item value.
    /// @param color Color index.
    /// @param fill Item area fill.
    /// @return True for success.
    Q_INVOKABLE bool addLineItem(int operation, QPoint point, QPoint end, int value, int color, int fill);

    /// @brief Add Text item.
    /// @param operation Item operation.
    /// @param point Text position.
    /// @param point End position.
    /// @param text Text string.
    /// @param size Text size.
    /// @param unit Size unit.
    /// @param color Color index.
    /// @param align Text alignment.
    /// @return True for success.
    Q_INVOKABLE bool addTextItem(int operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align);

    /// @brief Remove active item.
    /// @return True for success.
    /// @details Activates previous or first item.
    Q_INVOKABLE bool removeItem();

    /// @brief Get item count.
    /// @return Item count.
    Q_INVOKABLE int getItemCount() const;

    /// @brief Get item operation.
    /// @param index Item index.
    /// @return Item operation.
    Q_INVOKABLE int getItemOperation(int index) const;

    /// @brief Get item position.
    /// @param index Item index.
    /// @return Item position.
    Q_INVOKABLE QPoint getItemPosition(int index) const;

    /// @brief Get item data value.
    /// @param index Item index.
    /// @return Item value.
    /// @{
    Q_INVOKABLE int getItemValue(int index) const;
    Q_INVOKABLE QPoint getItemPoint(int index) const;
    Q_INVOKABLE QString getItemText(int index ) const;
    Q_INVOKABLE int getItemColor(int index) const;
    Q_INVOKABLE int getItemFill(int index) const;
    Q_INVOKABLE int getItemAlign(int index) const;
    Q_INVOKABLE double getItemSize(int index) const;
    Q_INVOKABLE int getItemUnit(int index) const;
    /// @}

    /// @brief Select item nearest to point.
    /// @\param point Point coordinates.
    /// @return Nearest item index.
    Q_INVOKABLE int selectItem(QPoint point) const;

    /// @brief Set active item index.
    /// @param index Active item index.
    /// @return True for success.
    Q_INVOKABLE bool setActiveIndex(int index);

    /// @brief Get active item index.
    /// @return Active item index.
    Q_INVOKABLE int getActiveIndex() const;

    /// @brief Cut symbol to clipboard.
    Q_INVOKABLE void cutClipboard();

    /// @brief Copy symbol to clipboard.
    Q_INVOKABLE void copyClipboard() const;

    /// @brief Paste symbol from clipboard.
    Q_INVOKABLE void pasteClipboard();

    /// @brief Rotate symbol.
    /// @param dir Positive value rotates right, negative left.
    Q_INVOKABLE void rotateSymbol(int dir);

    /// @brief Raise or lower item.
    /// @param dir Positive value raises, negative lowers.
    /// @return True for success.
    Q_INVOKABLE bool raiseItem(int dir);

    /// @brief Undo edit operation.
    /// @param undo True undoes, false redoes.
    /// @return True for success.
    Q_INVOKABLE bool undo(bool undo);

    /// @brief Open help.
    /// @param topic Help topic.
    Q_INVOKABLE void help(QString topic) const;

    /// @brief Open symbol file.
    /// @param fileurl File name as URL.
    /// @return True for success.
    Q_INVOKABLE bool open(QUrl fileurl);

    /// @brief Save symbol file.
    /// @param fileurl File name as URL.
    /// @return True for success.
    Q_INVOKABLE bool save(QUrl fileurl);

    /// @brief Check file name existence.
    /// @return True for existing file name.
    Q_INVOKABLE bool hasFilename() const;

    /// @brief Get file name without path.
    /// @return File name as url.
    Q_INVOKABLE QUrl getFilename() const;

    /// @brief Open symbol file.
    /// @param filename Full file path.
    /// @return True for success.
    bool open(const QString& filename);

    /// @brief Save symbol file.
    /// @param filename Full file path.
    /// @return True for success.
    bool save(const QString& filename);

    /// @brief Set language.
    /// @param lang Language abbreviation.
    void setLanguage(QString lang);

private:
    void undosave();

    bool Initialized = false;               ///< Initialization mutex.
    QString Filename;                       ///< Symbol file name.
    QString Language;                       ///< Language id.

    SymEditSymbol Symbol;                   ///< Current symbol.
    SymEditSettings Settings;               ///< Editor settings.

    std::deque<QString> UndoStack;          ///< Undo stack.
    std::deque<QString> RedoStack;          ///< Redo stack.
};
#endif
