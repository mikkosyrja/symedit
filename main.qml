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
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/clipboard_cut_icon&48.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/clipboard_copy_icon&48.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/clipboard_past_icon&48.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton { implicitWidth: 8 }
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/line_single.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/line_poly.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton { implicitWidth: 8 }
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/rectangle_corner.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/rectangle_center.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton { implicitWidth: 8 }
			ToolButton
			{
				width: 32; height: 32
				tooltip: qsTr("Circle Corners")	//%%
				Image
				{
					source: "image/circle_corner.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/circle_center.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/circle_horizontal.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			ToolButton
			{
				width: 32; height: 32
				Image
				{
					source: "image/circle_vertical.png"
					anchors.fill: parent
				}
				onClicked:
				{

				}
			}
			Item { Layout.fillWidth: true }
			CheckBox
			{
				id: fillcheck
				checked: fill
				text: qsTr("Fill")	//%%
				onClicked: { fill = !fill }
			}
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

	onFillChanged: { manager.setFill(fill); }
	onAlignChanged: { manager.setAlign(align); }
	onSnapChanged: { manager.setSnap(snap); }
	onToolChanged: { manager.setTool(tool); }

	Component.onCompleted:
	{
		x = manager.getWindowPos().x
		y = manager.getWindowPos().y
		width = manager.getWindowSize().width
		height = manager.getWindowSize().height

		fill = manager.getFill()
		align = manager.getAlign()
		snap = manager.getSnap()
		tool = manager.getTool()

		alignlist.setAlign()
		snaplist.setSnap()

		visible = true
		manager.setInitialized()
	}
}
