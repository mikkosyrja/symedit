import QtQuick 2.9
import QtQuick.Controls 1.4

import "TooltipCreator.js" as TooltipCreator

ToolButton
{
	property string image
	property int tool: 0

	implicitHeight: 32
	implicitWidth: 32
	z: 20
	Image
	{
		source: image
		anchors { fill: parent; margins: 4 }
	}

	onHoveredChanged:
	{
		if ( popup !== null )
			popup.hide()
		popup = TooltipCreator.create(tooltip, this)
		popup.show()
	}

	onClicked:
	{
		if ( tool )
			window.tool = tool
	}
}
