import QtQuick 2.9
import QtQuick.Controls 1.4

import "TooltipCreator.js" as TooltipCreator

ToolButton
{
	property string image
	property int tool: 0
	property var popup

	implicitHeight: 32
	implicitWidth: 32
	z: 20
	Image
	{
		source: image
		anchors { fill: parent; margins: 4 }
	}
/*
	ToolTip1
	{
		id: tooltip1
		width: 200
		target: parent
		text: tooltip
	}
*/

/*
	MouseArea
	{
		anchors.fill: parent
		hoverEnabled: true
		propagateComposedEvents: true

		onEntered:
		{
			popup = TooltipCreator.create(tooltip, this)
			popup.show()
		}
		onExited:
		{
			if ( popup !== null )
				popup.hide()
		}
	}
*/
	onHoveredChanged:
	{
		popup = TooltipCreator.create(tooltip, this)
		popup.show()
	}

	onClicked:
	{
		if ( tool )
			window.tool = tool
	}
}
