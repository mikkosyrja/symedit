import QtQuick 2.9
import QtQuick.Controls 1.4

ToolButton
{
	property int tool
	property string image

	implicitHeight: 32
	implicitWidth: 32
	Image
	{
		source: image
		anchors { fill: parent; margins: 4 }
	}
	onClicked:
	{
		window.tool = tool
	}
}
