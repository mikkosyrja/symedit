import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

ApplicationWindow
{
	property alias mousex: editor.mousex
	property alias mousey: editor.mousey
	property real snap: 5.0

	property int tool: 0
	property bool fill: false

	id: window
	visible: true
	width: 640; height: 480
	title: qsTr("Symbol editor")	//%%

	menuBar: MenuBar
	{
		Menu
		{
			title: "File"	//%%
			MenuItem
			{
				text: "Open"	//%%
				shortcut: "Ctrl+O"
				onTriggered:
				{
					//##
				}
			}
			MenuItem
			{
				text: "Save"	//%%
				shortcut: "Ctrl+S"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Exit"	//%%
				shortcut: "F4"
				onTriggered: { Qt.quit() }
			}
		}
		Menu
		{
			title: "Tool"	//%%
			MenuItem
			{
				text: "Select"	//%%
				checkable : true
				checked: (tool === Editor.Tool.Select)
				onTriggered: { tool = Editor.Tool.Select }
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Line"	//%%
				checkable : true
				checked: (tool === Editor.Tool.Line)
				onTriggered: { tool = Editor.Tool.Line }
			}
			MenuItem
			{
				text: "Polyline"	//%%
				checkable : true
				checked: (tool === Editor.Tool.Polyline)
				onTriggered: { tool = Editor.Tool.Polyline }
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Rectangle Center"	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCenter)
				onTriggered: { tool = Editor.Tool.RectangleCenter }
			}
			MenuItem
			{
				text: "Rectangle Corners"	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCorner)
				onTriggered: { tool = Editor.Tool.RectangleCorner }
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Circle Center"	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleCenter)
				onTriggered: { tool = Editor.Tool.CircleCenter }
			}
			MenuItem
			{
				text: "Circle Horizontal"	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleHorizontal)
				onTriggered: { tool = Editor.Tool.CircleHorizontal }
			}
			MenuItem
			{
				text: "Circle Vertical"	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleVertical)
				onTriggered: { tool = Editor.Tool.CircleVertical }
			}
			MenuItem
			{
				text: "Circle Corners"	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleCorner)
				onTriggered: { tool = Editor.Tool.CircleCorner }
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Semicircle"	//%%
				checkable : true
				checked: (tool === Editor.Tool.ArcSemicircle)
				onTriggered: { tool = Editor.Tool.ArcSemicircle }
			}
			MenuItem
			{
				text: "Quarter circle"	//%%
				checkable : true
				checked: (tool === Editor.Tool.ArcQuarter)
				onTriggered: { tool = Editor.Tool.ArcQuarter }
			}
			MenuSeparator { }
			MenuItem
			{
				text: "Text"	//%%
				checkable : true
				checked: (tool === Editor.Tool.Text)
				onTriggered: { tool = Editor.Tool.Text }
			}
		}
		Menu
		{
			title: "Help"	//%%
			MenuItem
			{
				text: "Help"	//%%
				shortcut: "F1"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: "About"	//%%
				onTriggered:
				{
					//##
				}
			}
		}
	}

	toolBar: ToolBar
	{
		RowLayout
		{
			anchors.fill: parent

			ToolButton { iconSource: "clear.png" }
			ToolButton { iconSource: "copy.png" }
			Item { Layout.fillWidth: true }
			CheckBox
			{
				id: fillcheck
				checked: fill
				text: "Fill"
				onClicked: { fill = !fill }
			}
			Label { text: "Alignment" }	//%%
			ComboBox
			{
				id: alignlist
				model: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
/*
				onCurrentIndexChanged:
				{
					if ( currentIndex == 0 ) { snap = 1 }
					else if ( currentIndex == 1 ) { snap = 2 }
					else if ( currentIndex == 2 ) { snap = 5 }
					else if ( currentIndex == 3 ) { snap = 10 }
				}
				function setsnap()
				{
					if ( snap == 1 ) { currentIndex = 0 }
					else if ( snap == 2 ) { currentIndex = 1 }
					else if ( snap == 10 ) { currentIndex = 3 }
					else { currentIndex = 2 }	// default 5
				}
*/
			}
			Label { text: "Snap" }	//%%
			ComboBox
			{
				id: snaplist
				model: [ 1, 2, 5, 10 ]
				onCurrentIndexChanged:
				{
					if ( currentIndex == 0 ) { snap = 1 }
					else if ( currentIndex == 1 ) { snap = 2 }
					else if ( currentIndex == 2 ) { snap = 5 }
					else if ( currentIndex == 3 ) { snap = 10 }
				}
				function setsnap()
				{
					if ( snap == 1 ) { currentIndex = 0 }
					else if ( snap == 2 ) { currentIndex = 1 }
					else if ( snap == 10 ) { currentIndex = 3 }
					else { currentIndex = 2 }	// default 5
				}
			}
		}
	}

	Editor
	{
		id: editor
	}

	statusBar: StatusBar
	{
		RowLayout
		{
			anchors.fill: parent
			Label { Layout.minimumWidth: 40; text: " X: " + mousex }
			Label {	Layout.minimumWidth: 40; text: " Y: " + mousey }
			Item { Layout.fillWidth: true }
		}
	}

	Component.onCompleted:
	{
		snaplist.setsnap()
		fill = true
		tool = Editor.Tool.Select
	}
}
