import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

ApplicationWindow
{
	property int mousex: 0
	property int mousey: 0

	property bool fillitem: false
	property int alignment: 1
	property real linewidth: 1.2
	property int snapgrid: 1
	property int tool: 0

	id: window
	visible: false
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
				text: qsTr("From Clipboard")	//%%
				shortcut: "Ctrl+Alt+V"
				onTriggered: { manager.readClipboard() }
			}
			MenuItem
			{
				text: qsTr("To Clipboard")	//%%
				shortcut: "Ctrl+Alt+C"
				onTriggered: { manager.writeClipboard() }
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
			title: qsTr("Edit")	//%%
			MenuItem
			{
				text: qsTr("Cut")	//%%
				shortcut: "Ctrl+X"
				onTriggered:
				{
					//##
				}
			}
			MenuItem
			{
				text: qsTr("Copy")	//%%
				shortcut: "Ctrl+C"
				onTriggered:
				{
					//##
				}
			}
			MenuItem
			{
				text: qsTr("Paste")	//%%
				shortcut: "Ctrl+V"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Up")	//%%
				shortcut: "Alt+Up"
				onTriggered:
				{
					//##
				}
			}
			MenuItem
			{
				text: qsTr("Down")	//%%
				shortcut: "Alt+Down"
				onTriggered:
				{
					//##
				}
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Delete")	//%%
				shortcut: "Delete"
				onTriggered:
				{
					//##
				}
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
				checked: (tool === Editor.Tool.LineSingle)
				onTriggered: { tool = Editor.Tool.LineSingle }
			}
			MenuItem
			{
				text: qsTr("Polyline")	//%%
				checkable : true
				checked: (tool === Editor.Tool.LinePoly)
				onTriggered: { tool = Editor.Tool.LinePoly }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Rectangle Corner")	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCorner)
				onTriggered: { tool = Editor.Tool.RectangleCorner }
			}
			MenuItem
			{
				text: qsTr("Rectangle Center")	//%%
				checkable : true
				checked: (tool === Editor.Tool.RectangleCenter)
				onTriggered: { tool = Editor.Tool.RectangleCenter }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Circle Corner")	//%%
				checkable : true
				checked: (tool === Editor.Tool.CircleCorner)
				onTriggered: { tool = Editor.Tool.CircleCorner }
			}
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
		Column
		{
			RowLayout
			{
				height: 32
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/folder_open_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/save_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton { implicitWidth: 8 }
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/clipboard_cut_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/clipboard_copy_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/clipboard_past_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/br_up_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/br_down_icon&48.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				ToolButton
				{
					implicitHeight: 32; implicitWidth: 32
					Image
					{
						source: "image/delete.png"
						anchors { fill: parent; margins: 4 }
					}
					onClicked:
					{

					}
				}
				Separator { }
				Tool { tool: Editor.Tool.LineSingle; image: "image/line_single.png" }
				Tool { tool: Editor.Tool.LinePoly; image: "image/line_poly.png" }
				Separator { }
				Tool { tool: Editor.Tool.RectangleCorner; image: "image/rectangle_corner.png" }
				Tool { tool: Editor.Tool.RectangleCenter; image: "image/rectangle_center.png" }
				Separator { }
				Tool { tool: Editor.Tool.CircleCorner; image: "image/circle_corner.png" }
				Tool { tool: Editor.Tool.CircleCenter; image: "image/circle_center.png" }
				Tool { tool: Editor.Tool.CircleHorizontal; image: "image/circle_horizontal.png" }
				Tool { tool: Editor.Tool.CircleVertical; image: "image/circle_vertical.png" }
				Separator { }
				Tool { tool: Editor.Tool.Text; image: "image/text.png" }
			}
			RowLayout
			{
				height: 32
				Item { Layout.fillWidth: true }
				CheckBox
				{
					id: fillcheck
					checked: fillitem
					text: qsTr("Fill")	//%%
					onClicked: { fillitem = !fillitem }
				}
				Separator { }
				Label { text: qsTr("Snap") }	//%%
				ComboBox
				{
					id: snaplist
					model: [ 1, 2, 5, 10 ]
					onCurrentIndexChanged:
					{
						if ( currentIndex == 0 ) { snapgrid = 1 }
						else if ( currentIndex == 1 ) { snapgrid = 2 }
						else if ( currentIndex == 2 ) { snapgrid = 5 }
						else if ( currentIndex == 3 ) { snapgrid = 10 }
					}
					function setSnap()
					{
						if ( snapgrid == 1 ) { currentIndex = 0 }
						else if ( snapgrid == 2 ) { currentIndex = 1 }
						else if ( snapgrid == 10 ) { currentIndex = 3 }
						else { currentIndex = 2 }	// default 5
					}
				}
				Separator { }
				Label { text: qsTr("Line width") }	//%%
				ComboBox
				{
					id: widthlist
					model: [ 1, 2 ]
/*
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
*/
				}
				Separator { }
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
			}
		}
	}

	Editor { id: editor }

	statusBar: StatusBar
	{
		RowLayout
		{
			anchors.fill: parent
			Label { Layout.minimumWidth: 40; text: " X: " + mousex }
			Label {	Layout.minimumWidth: 40; text: " Y: " + mousey }
			Item { Layout.fillWidth: true }
			Label {	Layout.minimumWidth: 40; text: manager.getSymbol() }
		}
	}

	onXChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onYChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onWidthChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onHeightChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }

	onFillitemChanged: { manager.setFillItem(fillitem); }
	onAlignmentChanged: { manager.setAlignment(alignment); }
	onLinewidthChanged: { manager.setLineWidth(linewidth * 10); }
	onSnapgridChanged: { manager.setSnapGrid(snapgrid); }
	onToolChanged: { manager.setTool(tool); }

	Component.onCompleted:
	{
		x = manager.getWindowPos().x
		y = manager.getWindowPos().y
		width = manager.getWindowSize().width
		height = manager.getWindowSize().height

		fillitem = manager.getFillItem()
		alignment = manager.getAlignment()
		linewidth = manager.getLineWidth() / 10
		snapgrid = manager.getSnapGrid()
		tool = manager.getTool()

		alignlist.setAlign()
		snaplist.setSnap()

		visible = true
		manager.setInitialized()
	}
}
