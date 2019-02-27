import QtQuick 2.9
import QtQuick.Controls 1.4

import "TooltipCreator.js" as TooltipCreator

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

	onHoveredChanged:
	{
		if ( popup !== null )
			popup.hide()
		if ( hovered )
		{
			popup = TooltipCreator.create(tooltip, this)
			popup.show()
		}
	}

	onPressedChanged:
	{
		if ( popup !== null )
			popup.hide()
	}

	onClicked:
	{
		if ( tool )
		{
			window.tool = tool	// clicking button seems to break binding
			checked = Qt.binding(function() { return (window.tool === tool) })
		}
	}
}
