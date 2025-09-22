import QtQuick
import QtQuick.Controls

ToolButton
{
    implicitWidth: 8

    // prevent clicking animation
    MouseArea { anchors.fill: parent }
}
