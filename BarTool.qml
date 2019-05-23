import QtQuick 2.9
import QtQuick.Controls 1.4

ToolButton
{
	property string image
	property int tool: 0

	implicitHeight: parent.height - 2
	implicitWidth: parent.height - 2
	z: 20

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
			window.tool = tool	// clicking button seems to break binding
			checked = Qt.binding(function() { return (window.tool === tool) })
		}
	}
}
