import QtQuick 2.9
import QtQuick.Controls 1.4

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
