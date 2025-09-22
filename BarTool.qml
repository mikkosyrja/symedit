import QtQuick
import QtQuick.Controls

ToolButton
{
    property string image
    property string tooltip
    property int tool: 0

    implicitHeight: parent.height - 2
    implicitWidth: parent.height - 2
    z: 20

    ToolTip.text: tooltip

    Image
    {
        source: image
        anchors { fill: parent; margins: 4 }
    }

    checkable: (tool !== 0)
    checked: (window.tool === tool)

    onClicked:
    {
        if ( tool )
        {
            window.tool = tool  // clicking button seems to break binding
            checked = Qt.binding(function() { return (window.tool === tool) })
        }
    }
}
