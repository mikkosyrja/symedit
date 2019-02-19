import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

ApplicationWindow
{
	property int mousex: 0
	property int mousey: 0

	property bool fillitem: false
	property int alignment: 1
	property real linewidth: 1
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
			MenuItem { text: qsTr("Open"); shortcut: "Ctrl+O"; onTriggered: open() }	//%%
			MenuItem { text: qsTr("Save"); shortcut: "Ctrl+S"; onTriggered: save() }	//%%
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
			MenuItem { text: qsTr("Exit"); shortcut: "F4"; onTriggered: Qt.quit() }		//%%
		}
		Menu
		{
			title: qsTr("Edit")	//%%
			MenuItem { text: qsTr("Cut"); shortcut: "Ctrl+X"; onTriggered: cut() }		//%%
			MenuItem { text: qsTr("Copy"); shortcut: "Ctrl+C"; onTriggered: copy() }	//%%
			MenuItem { text: qsTr("Paste"); shortcut: "Ctrl+V"; onTriggered: paste() }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Raise"); shortcut: "Alt+Up"; onTriggered: raise() }		//%%
			MenuItem { text: qsTr("Lower"); shortcut: "Alt+Down"; onTriggered: lower() }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Delete"); shortcut: "Delete"; onTriggered: remove() }	//%%
		}
		Menu
		{
			title: qsTr("Tool")	//%%
			MenuTool { text: qsTr("Select"); tool: Editor.Tool.Select }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Line"); tool: Editor.Tool.LineSingle }		//%%
			MenuTool { text: qsTr("Polyline"); tool: Editor.Tool.LinePoly }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Rectangle Corner"); tool: Editor.Tool.RectangleCorner }	//%%
			MenuTool { text: qsTr("Rectangle Center"); tool: Editor.Tool.RectangleCenter }	//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Circle Corner"); tool: Editor.Tool.CircleCorner }	//%%
			MenuTool { text: qsTr("Circle Radius"); tool: Editor.Tool.CircleRadius }	//%%
			MenuTool { text: qsTr("Circle Center"); tool: Editor.Tool.CircleCenter }	//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Semicircle"); tool: Editor.Tool.ArcSemicircle }		//%%
			MenuTool { text: qsTr("Quarter circle"); tool: Editor.Tool.ArcQuarter }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Text"); tool: Editor.Tool.Text }		//%%
		}
		Menu
		{
			title: qsTr("Help")	//%%
			MenuItem
			{
				text: qsTr("Help")	//%%
				shortcut: "F1"
				onTriggered: { help() }
			}
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("About")	//%%
				onTriggered: { about() }
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
				BarTool { image: "image/folder_open_icon&48.png"; onClicked: open() }
				BarTool { image: "image/save_icon&48.png"; onClicked: save() }
				BarSeparator { }
				BarTool { image: "image/clipboard_cut_icon&48.png"; onClicked: cut() }
				BarTool { image: "image/clipboard_copy_icon&48.png"; onClicked: copy() }
				BarTool { image: "image/clipboard_past_icon&48.png"; onClicked: paste() }
				BarTool { image: "image/br_up_icon&48.png"; onClicked: raise() }
				BarTool { image: "image/br_down_icon&48.png"; onClicked: lower() }
				BarTool { image: "image/delete.png"; onClicked: remove() }
				BarSeparator { }
				BarTool { image: "image/cursor_arrow_icon&48.png"; tool: Editor.Tool.Select }
				BarSeparator { }
				BarTool { image: "image/line_single.png"; tool: Editor.Tool.LineSingle }
				BarTool { image: "image/line_poly.png"; tool: Editor.Tool.LinePoly }
				BarSeparator { }
				BarTool { image: "image/rectangle_corner.png"; tool: Editor.Tool.RectangleCorner }
				BarTool { image: "image/rectangle_center.png"; tool: Editor.Tool.RectangleCenter }
				BarSeparator { }
				BarTool { image: "image/circle_corner.png"; tool: Editor.Tool.CircleCorner }
				BarTool { image: "image/circle_radius.png"; tool: Editor.Tool.CircleRadius }
				BarTool { image: "image/circle_center.png"; tool: Editor.Tool.CircleCenter }
				BarSeparator { }
				BarTool { image: "image/text.png"; tool: Editor.Tool.Text }
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
				BarSeparator { }
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
				BarSeparator { }
				Label { text: qsTr("Line width") }	//%%
				ComboBox
				{
					id: widthlist
					model: [ 1, 2, 3, 4, 5 ]
					onCurrentIndexChanged: { linewidth = currentIndex + 1 }
					function setWidth() { currentIndex = linewidth - 1 }
				}
				BarSeparator { }
				Label { text: qsTr("Alignment") }	//%%
				ComboBox
				{
					id: alignlist
					model: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
					onCurrentIndexChanged: { alignment = currentIndex + 1 }
					function setAlign() { currentIndex = alignment - 1 }
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
	onLinewidthChanged: { manager.setLineWidth(linewidth); }
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
		linewidth = manager.getLineWidth()
		snapgrid = manager.getSnapGrid()
		tool = manager.getTool()

		snaplist.setSnap()
		widthlist.setWidth()
		alignlist.setAlign()

		visible = true
		manager.setInitialized()
	}

	function open()
	{

	}

	function save()
	{

	}

	function cut()
	{

	}

	function copy()
	{

	}

	function paste()
	{

	}

	function raise()
	{

	}

	function lower()
	{

	}

	function remove()
	{

	}

	function help()
	{

	}

	function about()
	{

	}
}
