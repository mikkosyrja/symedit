#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>

#include <QPoint>
#include <QString>
#include <QObject>

namespace Operation             ///< Item operation namespace.
{
    Q_NAMESPACE
    enum Type                   ///< Item operation type.
    {
        None = 0,               ///< No operation.
        Line = 1,               ///< Straight line with two points.
        Rectangle = 2,          ///< Rectangle with two corners.
        Circle = 3,             ///< Circle with center and radius.
        Text = 4,               ///< Text with single position point.
        Arc = 5                 ///< Semicircle with two endpoints.
    };
    Q_ENUM_NS(Type)
}

//! Symbol class.
class SymEditSymbol
{
public:
    /// @brief Constructor.
    SymEditSymbol();

    class Item                  ///< Symbol item.
    {
    public:
        /// @brief Constructor.
        Item();

        //! Constructor.
        /// @param operation Item operation.
        /// @param point Item position.
        /// @param end End position.
        /// @param value Item value.
        /// @param color Item color index.
        /// @param fill Item area fill.
        Item(Operation::Type operation, QPoint point, QPoint end, int value, int color, int fill);

        /// @brief Constructor.
        /// @param operation Item operation.
        /// @param point Item position.
        /// @param end End position.
        /// @param text Text string.
        /// @param size Text size.
        /// @param unit Size unit.
        /// @param color Item color index.
        /// @param align Text alignment.
        Item(Operation::Type operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align);

        Operation::Type Operation;  ///< Item operation.
        QPoint Point;               ///< Item coordinates.
        QPoint End;                 ///< End coordinates.
        QString Text;               ///< Text string.
        double Size;                ///< Text size.
        int Value;                  ///< Item value.
        int Color;                  ///< Color index.
        int Fill;                   ///< Fill area.
        int Align;                  ///< Text alignment.
        int Unit;                   ///< Size unit.
    };

    /// @brief Load symbol from string.
    /// @param buffer String buffer.
    void Load(const QString& buffer);

    /// @brief Save symbol to string.
    /// @param buffer String buffer.
    /// @param rich True for rich text with layout.
    /// @return Reference to buffer.
    QString& Save(QString& buffer, bool rich = false) const;

    /// @brief Clear symbol.
    void Clear();

    /// @brief Add symbol item.
    /// @param operation Item operation.
    /// @param point Start position.
    /// @param end End position.
    /// @param value Item value.
    /// @param color Item color index.
    /// @param fill Item area fill.
    /// @return Reference to item.
    Item& AddItem(Operation::Type operation, QPoint point, QPoint end, int value, int color, int fill);

    /// @brief Add symbol item.
    /// @param operation Item operation.
    /// @param point Start position.
    /// @param end End position.
    /// @param text Text string.
    /// @param size Text size.
    /// @param unit Size unit.
    /// @param color Item color index.
    /// @param align Text alignment.
    /// @return Reference to item.
    Item& AddItem(Operation::Type operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align);

    /// @brief Remove item.
    /// @param index Item index.
    /// @return True for success.
    /// @details Activates previous or first item.
    bool RemoveItem(int index);

    /// @brief Select item nearest to point.
    /// @param point Point coordinates.
    /// @return Nearest item index.
    int SelectItem(QPoint point) const;

    /// @brief Set active item index.
    /// @param index Active item index or -1 for deactivation.
    /// @return True for success.
    bool SetActiveIndex(int index);

    /// @brief Get active item index.
    /// @return Active item index.
    int GetActiveIndex() const;

    /// @brief Get item count.
    /// @return Item count.
    int GetItemCount() const;

    /// @brief Get item from index.
    /// @param index Item index.
    /// @return Item from index.
    const Item& GetItem(int index) const;

    /// @brief Rotate symbol.
    /// @param dir Positive value rotates right, negative left
    void RotateSymbol(int dir);

    /// @brief Raise or lower item.
    /// @param dir Positive value raises, negative lowers.
    /// @return True for success.
    bool RaiseItem(int dir);

private:
    std::vector<Item> Items;        ///< Symbol items.

    mutable int ActiveIndex;        ///< Active item index.
};

#endif
