import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

ApplicationWindow
{
	property int mousex: 0
	property int mousey: 0

	property bool fill: false
	property int align: 1
	property int snap: 1
	property int tool: 0

	id: window
	x: 500
	y: 100
	visible: true
	width: 640; height: 480
	title: qsTr("Symbol editor")	//%%

	menuBar: MenuBar
	{
		Menu
		{
			title: qsTr("File")	//%%
			MenuItem
			{
				text: qsTr("Open")	//%%
				shortcut: "Ctrl+O"
				onTriggered:
				{
					//##
				}
			}
			MenuItem
			{
				text: qsTr("Save")	//%%
				shortcut: "Ctrl+S"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Exit")	//%%
				shortcut: "F4"
				onTriggered: { Qt.quit() }
			}
		}
		Menu
		{
			title: qsTr("Tool")	//%%
			MenuItem
			{
				text: qsTr("Select")	//%%
				checkable : true
				checked: (tool === Editor.Tool.Select)
				onTriggered: { tool = Editor.Tool.Select }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Line")	//%%
				checkable : true
				checked: (tool === Editor.Tool.Line)
				onTriggered: { tool = Editor.Tool.Line }
			}
			MenuItem
			{
				text: qsTr("Polyline")	//%%
				checkable : true
				checked: (tool === Editor.Tool.Polyline)
				onTriggered: { tool = Editor.Tool.Polyline }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Rectangle Center")	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCenter)
				onTriggered: { tool = Editor.Tool.RectangleCenter }
			}
			MenuItem
			{
				text: qsTr("Rectangle Corners")	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCorner)
				onTriggered: { tool = Editor.Tool.RectangleCorner }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Circle Center")	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleCenter)
				onTriggered: { tool = Editor.Tool.CircleCenter }
			}
			MenuItem
			{
				text: qsTr("Circle Horizontal")	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleHorizontal)
				onTriggered: { tool = Editor.Tool.CircleHorizontal }
			}
			MenuItem
			{
				text: qsTr("Circle Vertical")	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleVertical)
				onTriggered: { tool = Editor.Tool.CircleVertical }
			}
			MenuItem
			{
				text: qsTr("Circle Corners")	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleCorner)
				onTriggered: { tool = Editor.Tool.CircleCorner }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Semicircle")	//%%
				checkable : true
				checked: (tool === Editor.Tool.ArcSemicircle)
				onTriggered: { tool = Editor.Tool.ArcSemicircle }
			}
			MenuItem
			{
				text: qsTr("Quarter circle")	//%%
				checkable : true
				checked: (tool === Editor.Tool.ArcQuarter)
				onTriggered: { tool = Editor.Tool.ArcQuarter }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Text")	//%%
				checkable : true
				checked: (tool === Editor.Tool.Text)
				onTriggered: { tool = Editor.Tool.Text }
			}
		}
		Menu
		{
			title: qsTr("Help")	//%%
			MenuItem
			{
				text: qsTr("Help")	//%%
				shortcut: "F1"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("About")	//%%
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
			Label { text: qsTr("Alignment") }	//%%
			ComboBox
			{
				id: alignlist
				model: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
				onCurrentIndexChanged:
				{
/*
					if ( currentIndex == 0 ) { snap = 1 }
					else if ( currentIndex == 1 ) { snap = 2 }
					else if ( currentIndex == 2 ) { snap = 5 }
					else if ( currentIndex == 3 ) { snap = 10 }
*/
				}
				function setAlign()
				{
/*
					if ( snap == 1 ) { currentIndex = 0 }
					else if ( snap == 2 ) { currentIndex = 1 }
					else if ( snap == 10 ) { currentIndex = 3 }
					else { currentIndex = 2 }	// default 5
*/
				}
			}
			Label { text: qsTr("Snap") }	//%%
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
				function setSnap()
				{
					if ( snap == 1 ) { currentIndex = 0 }
					else if ( snap == 2 ) { currentIndex = 1 }
					else if ( snap == 10 ) { currentIndex = 3 }
					else { currentIndex = 2 }	// default 5
				}
			}
			CheckBox
			{
				id: fillcheck
				checked: fill
				text: qsTr("Fill")	//%%
				onClicked: { fill = !fill }
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

	onXChanged: { manager.setPosition(Qt.point(x, y)) }
	onYChanged: { manager.setPosition(Qt.point(x, y)) }
	onWidthChanged: { manager.setSize(Qt.size(width, height)) }
	onHeightChanged: { manager.setSize(Qt.size(width, height)) }

	onFillChanged: { manager.setFill(fill); }
	onAlignChanged: { manager.setAlign(align); }
	onSnapChanged: { manager.setSnap(snap); }
	onToolChanged: { manager.setTool(tool); }

	Component.onCompleted:
	{
		x = manager.getPosition().x
		y = manager.getPosition().y
		width = manager.getSize().width
		height = manager.getSize().height

		fill = manager.getFill()
		align = manager.getAlign()
		snap = manager.getSnap()
		tool = manager.getTool()

		alignlist.setAlign()
		snaplist.setSnap()
	}
}
