#include <QGuiApplication>
#include <QScreen>
#include <QClipboard>
#include <QSettings>
#include <QDesktopServices>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>

#include <QMessageBox>

#include "symedit.hpp"

//
//  settings functions
//
SymEditSettings::SymEditSettings()
{
    IntValues.emplace("SnapGrid", 5);
    IntValues.emplace("LineWidth", 1);
    IntValues.emplace("ColorIndex", 1);
    IntValues.emplace("FillItem", 0);
    IntValues.emplace("Alignment", 9);
    IntValues.emplace("SizeUnit", 0);
    IntValues.emplace("Tool", 1);

    RealValues.emplace("SymbolSize", 5.0);
    RealValues.emplace("TextSize", 0.0);

    TextValues.emplace("Language", "");
    TextValues.emplace("TextValue", "");
    TextValues.emplace("Directory", "");
}

void SymEditSettings::Load()
{
    QSettings settings;

    QSize size = QGuiApplication::primaryScreen()->size();
    Position.setX(settings.value("window/x", size.width() / 4).toInt());
    Position.setY(settings.value("window/y", size.height() / 6).toInt());
    Size.setWidth(settings.value("window/width", size.width() / 2).toInt());
    Size.setHeight(settings.value("window/height", size.height() * 2 / 3).toInt());

    TextValues.at("Directory") = settings.value("application/directory").toString();

    IntValues.at("SnapGrid") = settings.value("editor/snap", 5).toInt();
    IntValues.at("LineWidth") = settings.value("editor/width", 1).toInt();
    RealValues.at("SymbolSize") = settings.value("editor/symbol", 5.0).toDouble();
    TextValues.at("Language") = settings.value("editor/lang").toString();

//  IntValues.at("ColorIndex") = settings.value("editor/color", 1).toInt();
//  IntValues.at("FillItem") = settings.value("editor/fill", 0).toInt();
//  RealValues.at("TextSize") = settings.value("editor/size", 0.0).toDouble();
    IntValues.at("Alignment") = settings.value("editor/align", 9).toInt();
    IntValues.at("SizeUnit") = settings.value("editor/unit", 0).toInt();

    TextValues.at("TextValue") = settings.value("editor/text").toString();
    IntValues.at("Tool") = settings.value("editor/tool", 1).toInt();
}

void SymEditSettings::Save() const
{
    QSettings settings;

    settings.setValue("window/x", Position.x());
    settings.setValue("window/y", Position.y());
    settings.setValue("window/width", Size.width());
    settings.setValue("window/height", Size.height());

    settings.setValue("application/directory", TextValues.at("Directory"));

    settings.setValue("editor/snap", IntValues.at("SnapGrid"));
    settings.setValue("editor/width", IntValues.at("LineWidth"));
    settings.setValue("editor/symbol", RealValues.at("SymbolSize"));
    settings.setValue("editor/lang", TextValues.at("Language"));

    settings.setValue("editor/color", IntValues.at("ColorIndex"));
    settings.setValue("editor/fill", IntValues.at("FillItem"));
    settings.setValue("editor/size", RealValues.at("TextSize"));
    settings.setValue("editor/align", IntValues.at("Alignment"));
    settings.setValue("editor/unit", IntValues.at("SizeUnit"));

    settings.setValue("editor/text", TextValues.at("TextValue"));
    settings.setValue("editor/tool", IntValues.at("Tool"));
}

//
//  manager functions
//
SymEditManager::SymEditManager(QObject* parent) : QObject(parent)
{
    Settings.Load();
}

SymEditManager::SymEditManager(const QString& filename, const QString& symbol)
    : QObject(nullptr), Filename(filename)
{
    Settings.Load();

    if ( !Filename.isEmpty() )
        open(Filename);

    if ( !symbol.isEmpty() )
        Symbol.Load(symbol);
}

void SymEditManager::setInitialized()
{
    Initialized = true;
}

void SymEditManager::setGeometry(QPoint point, QSize size)
{
    if ( Initialized )
    {
        Settings.Position = point;
        Settings.Size = size;
    }
}

QPoint SymEditManager::getWindowPos() const
{
    return Settings.Position;
}

QSize SymEditManager::getWindowSize() const
{
    return Settings.Size;
}

void SymEditManager::setIntSetting(QString name, int value)
{
    if ( Settings.IntValues.find(name) != Settings.IntValues.end() )
        Settings.IntValues.at(name) = value;
}
void SymEditManager::setRealSetting(QString name, double value)
{
    if ( Settings.RealValues.find(name) != Settings.RealValues.end() )
        Settings.RealValues.at(name) = value;
}
void SymEditManager::setTextSetting(QString name, QString value)
{
    if ( Settings.TextValues.find(name) != Settings.TextValues.end() )
        Settings.TextValues.at(name) = value;
}

int SymEditManager::getIntSetting(QString name) const
{
    if ( Settings.IntValues.find(name) != Settings.IntValues.end() )
        return Settings.IntValues.at(name);
    return 0;
}
double SymEditManager::getRealSetting(QString name) const
{
    if ( Settings.RealValues.find(name) != Settings.RealValues.end() )
        return Settings.RealValues.at(name);
    return 0;
}
QString SymEditManager::getTextSetting(QString name) const
{
    if ( Settings.TextValues.find(name) != Settings.TextValues.end() )
        return Settings.TextValues.at(name);
    return QString();
}

QString SymEditManager::getSymbol(bool rich) const
{
    QString buffer;
    return Symbol.Save(buffer, rich);
}

bool SymEditManager::addPointItem(int operation, QPoint point, int value, int color, int fill)
{
    undosave();
    Symbol.AddItem(static_cast<Operation::Type>(operation), point, point, value, color, fill);
    return true;
}

bool SymEditManager::addLineItem(int operation, QPoint point, QPoint end, int value, int color, int fill)
{
    undosave();
    Symbol.AddItem(static_cast<Operation::Type>(operation), point, end, value, color, fill);
    return true;
}

bool SymEditManager::addTextItem(int operation, QPoint point, QPoint end, QString text, double size, int unit, int color, int align)
{
    if ( !text.isEmpty() )
    {
        undosave();
        Symbol.AddItem(static_cast<Operation::Type>(operation), point, end, text, size, unit, color, align);
        return true;
    }
    return false;
}

bool SymEditManager::removeItem()
{
    if ( Symbol.GetItemCount() )
    {
        undosave();
        return Symbol.RemoveItem(Symbol.GetActiveIndex());
    }
    return false;
}

int SymEditManager::getItemCount() const
{
    return Symbol.GetItemCount();
}

int SymEditManager::getItemOperation(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Operation;
    return Operation::None;
}

QPoint SymEditManager::getItemPosition(int index) const
{
    if ( Symbol.GetItemCount() )
    {
        const auto& item = Symbol.GetItem(index);
        if ( item.Operation == Operation::Rectangle )   // normalize to upper left
            return QPoint(std::min(item.End.x(), item.Point.x()), std::max(item.End.y(), item.Point.y()));
        return item.Point;
    }
    return QPoint(0, 0);
}

int SymEditManager::getItemValue(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Value;
    return 0;
}
QPoint SymEditManager::getItemPoint(int index) const
{
    if ( Symbol.GetItemCount() )
    {
        const auto& item = Symbol.GetItem(index);
        if ( item.Operation == Operation::Rectangle )   // normalize to lower right
            return QPoint(std::max(item.End.x(), item.Point.x()), std::min(item.End.y(), item.Point.y()));
        return item.End;
    }
    return QPoint(0, 0);
}
QString SymEditManager::getItemText(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Text;
    return "";
}
int SymEditManager::getItemColor(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Color;
    return 1;
}
int SymEditManager::getItemFill(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Fill;
    return 0;
}
int SymEditManager::getItemAlign(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Align;
    return 0;
}
double SymEditManager::getItemSize(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Size;
    return 0.0;
}
int SymEditManager::getItemUnit(int index) const
{
    if ( Symbol.GetItemCount() )
        return Symbol.GetItem(index).Unit;
    return 0;
}

int SymEditManager::selectItem(QPoint point) const
{
    return Symbol.SelectItem(point);
}

bool SymEditManager::setActiveIndex(int index)
{
    return Symbol.SetActiveIndex(index);
}

int SymEditManager::getActiveIndex() const
{
    return Symbol.GetActiveIndex();
}

void SymEditManager::cutClipboard()
{
    if ( QClipboard* clipboard = QGuiApplication::clipboard() )
    {
        undosave();
        clipboard->setText(getSymbol(false));
        Symbol.Clear();
    }
}

void SymEditManager::copyClipboard() const
{
    if ( QClipboard* clipboard = QGuiApplication::clipboard() )
        clipboard->setText(getSymbol(false));
}

void SymEditManager::pasteClipboard()
{
    if ( QClipboard* clipboard = QGuiApplication::clipboard() )
    {
        undosave();
        Symbol.Load(clipboard->text());
    }
}

void SymEditManager::rotateSymbol(int dir)
{
    undosave();
    Symbol.RotateSymbol(dir);
}

bool SymEditManager::raiseItem(int dir)
{
    if ( Symbol.GetItemCount() )
    {
        undosave();
        return Symbol.RaiseItem(dir);
    }
    return false;
}

bool SymEditManager::undo(bool undo)
{
    if ( undo )
    {
        if ( UndoStack.empty() )
            return false;

        QString buffer;
        Symbol.Save(buffer);
        RedoStack.push_back(buffer);

        Symbol.Load(UndoStack.back());
        UndoStack.pop_back();
        return true;
    }
    if ( RedoStack.empty() )
        return false;

    QString buffer;
    Symbol.Save(buffer);
    UndoStack.push_back(buffer);

    Symbol.Load(RedoStack.back());
    RedoStack.pop_back();
    return true;
}

/// @brief Save item to undo stack.
void SymEditManager::undosave()
{
    QString buffer;
    Symbol.Save(buffer);
    UndoStack.push_back(buffer);
    RedoStack.clear();
}

void SymEditManager::help(QString topic) const
{
    Q_UNUSED(topic);
    QString path = QCoreApplication::applicationDirPath();
    path.append("/help/").append(Language).append("/symedit/index.html");
    if ( QFileInfo(path).exists() )     // release
        QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
    else    // development
    {
        path = QCoreApplication::applicationDirPath();
        path.append("/../threedee/help/").append(Language).append("/symedit/index.html");
        if ( QFileInfo(path).exists() )     // visual studio
            QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
        else    // qt creator
        {
            path = QCoreApplication::applicationDirPath();
            path.append("/../../symedit/help/").append(Language).append("/_build/html/index.html");
            if ( QFileInfo(path).exists() )     // windows
                QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
            else    // linux
            {
                path = QCoreApplication::applicationDirPath();
                path.append("/../symedit/help/").append(Language).append("/_build/html/index.html");
                if ( QFileInfo(path).exists() )
                    QDesktopServices::openUrl(QUrl(path.insert(0, "file:///"), QUrl::TolerantMode));
            }
        }
    }
}

bool SymEditManager::open(QUrl fileurl)
{
    QString filestring = fileurl.toString();
    int index = filestring.lastIndexOf('/') + 1;
    QString directory = filestring.left(index);
    setTextSetting("Directory", directory);
    return open(fileurl.toLocalFile());
}

bool SymEditManager::save(QUrl fileurl)
{
    QString filename = Filename;
    if ( !fileurl.isEmpty() )
    {
        QString filestring = fileurl.toString();
        int index = filestring.lastIndexOf('/') + 1;
        QString directory = filestring.left(index);
        setTextSetting("Directory", directory);
        filename = fileurl.toLocalFile();
    }
    return save(filename);
}

bool SymEditManager::hasFilename() const
{
    return !Filename.isEmpty();
}

QUrl SymEditManager::getFilename() const
{
    int index = Filename.lastIndexOf('/');
    return QUrl(Filename.mid(index + 1));
}

bool SymEditManager::open(const QString& filename)
{
    QFile file(filename);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream input(&file);
        Symbol.Load(input.readLine());
        Filename = filename;
        return true;
    }
    return false;
}

bool SymEditManager::save(const QString& filename)
{
    QFile file(filename);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream output(&file);
        output << getSymbol(false);
        Filename = filename;
        return true;
    }
    return false;
}

void SymEditManager::setLanguage(QString lang)
{
    Language = lang;
}
