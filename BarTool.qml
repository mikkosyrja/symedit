import QtQuick 2.9
import QtQuick.Controls 1.4

ToolButton
{
	property string image
	property int tool: 0

	implicitHeight: 32
	implicitWidth: 32
	Image
	{
		source: image
		anchors { fill: parent; margins: 4 }
	}
	onClicked:
	{
		if ( tool )
			window.tool = tool
	}
}
