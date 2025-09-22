import QtQuick
import QtQuick.Controls

MenuItem
{
    property int tool: 0

    checkable : true
    checked: (window.tool === tool)
    onTriggered:
    {
        if ( tool )
            window.tool = tool
    }
}
