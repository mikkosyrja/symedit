import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

ApplicationWindow
{
	property int mousex: 0
	property int mousey: 0

	property bool viewgrid: true
	property real zoomscale: 1.0
	property real zoomstep: 1.3

	property int fillitem: 0
	property real linewidth: 1
	property int alignment: 1
	property int textsize: 1
	property int snapgrid: 1
	property int tool: 0

	property string symbol
	property var popup: null

	id: window
	visible: false
	title: qsTr("Symbol editor")	//%%

	menuBar: MenuBar
	{
		Menu
		{
			title: qsTr("File")		//%%
			MenuItem { text: qsTr("Open"); shortcut: "Ctrl+O"; onTriggered: open() }	//%%
			MenuItem { text: qsTr("Save"); shortcut: "Ctrl+S"; onTriggered: save() }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Exit"); shortcut: "F4"; onTriggered: Qt.quit() }		//%%
		}
		Menu
		{
			title: qsTr("Edit")		//%%
			MenuItem { text: qsTr("Undo"); shortcut: "Ctrl+Z"; onTriggered: undo(true) }	//%%
			MenuItem { text: qsTr("Redo"); shortcut: "Ctrl+Y"; onTriggered: undo(false) }	//%%
//			MenuItem { text: qsTr("Redo"); shortcut: "Ctrl+Y,Ctrl+Shift+Z"; onTriggered: undo(false) }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Cut"); shortcut: "Ctrl+X"; onTriggered: cut() }		//%%
			MenuItem { text: qsTr("Copy"); shortcut: "Ctrl+C"; onTriggered: copy() }	//%%
			MenuItem { text: qsTr("Paste"); shortcut: "Ctrl+V"; onTriggered: paste() }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Rotate Right"); shortcut: "Alt+Right"; onTriggered: rotate(1) }	//%%
			MenuItem { text: qsTr("Rotate Left"); shortcut: "Alt+Left"; onTriggered: rotate(-1) }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Raise Item"); shortcut: "Alt+Up"; onTriggered: raise(1) }		//%%
			MenuItem { text: qsTr("Lower Item"); shortcut: "Alt+Down"; onTriggered: raise(-1) }		//%%
			MenuSeparator { }
			MenuItem { text: qsTr("Delete"); shortcut: "Delete"; onTriggered: remove() }	//%%
		}
		Menu
		{
			title: qsTr("View")		//%%
			MenuItem { text: qsTr("Zoom In"); shortcut: "Ctrl++"; onTriggered: zoom(1) }	//%%
			MenuItem { text: qsTr("Zoom Out"); shortcut: "Ctrl+-"; onTriggered: zoom(-1) }	//%%
			MenuItem { text: qsTr("Zoom All"); shortcut: "Ctrl+0"; onTriggered: zoom(0) }	//%%
			MenuSeparator { }
			MenuItem
			{
				text: qsTr("Grid"); shortcut: "Ctrl+G"		//%%
				checkable : true; checked: viewgrid
				onTriggered: grid()
			}
		}
		Menu
		{
			title: qsTr("Tool")		//%%
			MenuTool { text: qsTr("Select"); tool: Editor.Tool.Select }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Line"); tool: Editor.Tool.Line }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Rectangle Corner"); tool: Editor.Tool.RectCorner }	//%%
			MenuTool { text: qsTr("Rectangle Center"); tool: Editor.Tool.RectCenter }	//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Circle Corner"); tool: Editor.Tool.CircleCorner }	//%%
			MenuTool { text: qsTr("Circle Radius"); tool: Editor.Tool.CircleRadius }	//%%
			MenuTool { text: qsTr("Circle Center"); tool: Editor.Tool.CircleCenter }	//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Semicircle"); tool: Editor.Tool.ArcSemi }			//%%
			MenuTool { text: qsTr("Quarter circle"); tool: Editor.Tool.ArcQuarter }		//%%
			MenuSeparator { }
			MenuTool { text: qsTr("Text"); tool: Editor.Tool.Text }		//%%
		}
		Menu
		{
			title: qsTr("Help")		//%%
			MenuItem { text: qsTr("Help"); shortcut: "F1"; onTriggered: help() }	//%%
			MenuSeparator { }
			MenuItem { text: qsTr("About"); onTriggered: about() }		//%%
		}
	}

	toolBar: ToolBar
	{
		Column
		{
			RowLayout
			{
				height: 32
				z: 10
//				BarTool { image: "image/open_icon&48.png"; tooltip: "Open File"; onClicked: open() }	//%%
//				BarTool { image: "image/save_icon&48.png"; tooltip: "Save File"; onClicked: save() }	//%%
//				BarSeparator { }
				BarTool { image: "image/undo_icon&48.png"; tooltip: "Undo Edit"; onClicked: undo(true) }	//%%
				BarTool { image: "image/redo_icon&48.png"; tooltip: "Redo Edit"; onClicked: undo(false) }	//%%
				BarTool { image: "image/cut_icon&48.png"; tooltip: "Cut Symbol"; onClicked: cut() }			//%%
				BarTool { image: "image/copy_icon&48.png"; tooltip: "Copy Symbol"; onClicked: copy() }		//%%
				BarTool { image: "image/paste_icon&48.png"; tooltip: "Paste symbol"; onClicked: paste() }	//%%
				BarSeparator { }
				BarTool { image: "image/rotate_right.png"; tooltip: "Rotate right"; onClicked: rotate(1) }	//%%
				BarTool { image: "image/rotate_left.png"; tooltip: "Rotate left"; onClicked: rotate(-1) }	//%%
				BarTool { image: "image/up_icon&48.png"; tooltip: "Raise item"; onClicked: raise(1) }		//%%
				BarTool { image: "image/down_icon&48.png"; tooltip: "Lower item"; onClicked: raise(-1) }	//%%
				BarTool { image: "image/delete.png"; tooltip: "Delete item"; onClicked: remove() }			//%%
				BarSeparator { }
				BarTool { image: "image/cursor_icon&48.png"; tooltip: "Select item"; tool: Editor.Tool.Select }	//%%
				BarSeparator { }
				BarTool { image: "image/polyline.png"; tooltip: "Straight Line"; tool: Editor.Tool.Line }	//%%
				BarSeparator { }
				BarTool { image: "image/rectangle_corner.png"; tooltip: "Rectangle Corners"; tool: Editor.Tool.RectCorner }	//%%
				BarTool { image: "image/rectangle_center.png"; tooltip: "Rectangle Center"; tool: Editor.Tool.RectCenter }	//%%
				BarSeparator { }
				BarTool { image: "image/circle_corner.png"; tooltip: "Circle Corner"; tool: Editor.Tool.CircleCorner }	//%%
				BarTool { image: "image/circle_radius.png"; tooltip: "Circle Radius"; tool: Editor.Tool.CircleRadius }	//%%
				BarTool { image: "image/circle_center.png"; tooltip: "Circle Center"; tool: Editor.Tool.CircleCenter }	//%%
				BarSeparator { }
				BarTool { image: "image/text.png"; tooltip: "Text String"; tool: Editor.Tool.Text }		//%%
			}
			RowLayout
			{
				height: 32
				Label { text: qsTr("Snap") }	//%%
				ComboBox
				{
					id: snaplist
					implicitWidth: 50
					model: [ 1, 5, 10 ]
					onCurrentIndexChanged:
					{
						if ( currentIndex == 0 ) { snapgrid = 1 }
						else if ( currentIndex == 1 ) { snapgrid = 5 }
						else if ( currentIndex == 2 ) { snapgrid = 10 }
					}
					function setSnap()
					{
						if ( snapgrid == 1 ) { currentIndex = 0 }
						else if ( snapgrid == 10 ) { currentIndex = 2 }
						else { currentIndex = 1 }	// default 5
					}
				}
				BarSeparator { }
				Item { Layout.fillWidth: true }
				Label { text: qsTr("Fill") }	//%%
				ComboBox
				{
					id: filllist
					implicitWidth: 100
					model: [ "No fill", "Area fill", "Backgroud" ]	//%%
//					model: [ "Ei täyttöä", "Aluetäyttö", "Taustaväri" ]	//%%
					onCurrentIndexChanged: { fillitem = currentIndex; editor.update() }
					function setFill() { currentIndex = fillitem }
				}
				BarSeparator { }
				Label { text: qsTr("Line width") }	//%%
				ComboBox
				{
					id: widthlist
					implicitWidth: 50
					model: [ 1, 2, 3, 4, 5 ]
					onCurrentIndexChanged: { linewidth = currentIndex + 1; editor.update() }
					function setWidth() { currentIndex = linewidth - 1 }
				}
				BarSeparator { }
				Label { text: qsTr("Text size") }	//%%
				ComboBox
				{
					id: sizelist
					implicitWidth: 50
					model: [ 1, 2, 3, 4, 5 ]
					onCurrentIndexChanged: { textsize = currentIndex + 1; editor.update() }
					function setSize() { currentIndex = textsize - 1 }
				}
				BarSeparator { }
				Label { text: qsTr("Alignment") }	//%%
				ComboBox
				{
					id: alignlist
					implicitWidth: 50
					model: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
					onCurrentIndexChanged: { alignment = currentIndex + 1 }
					function setAlign() { currentIndex = alignment - 1 }
				}
				BarSeparator { }
				Label { text: qsTr("Text") }	//%%
				TextField
				{
					id: textfield
					implicitWidth: 120


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
			Label {	Layout.minimumWidth: 40; text: symbol }
		}
	}

	onXChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onYChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onWidthChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onHeightChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }

	onFillitemChanged: { manager.setIntSetting("FillItem", fillitem); }
	onAlignmentChanged: { manager.setIntSetting("Alignment", alignment); }
	onLinewidthChanged: { manager.setIntSetting("LineWidth", linewidth); }
	onTextsizeChanged: { manager.setIntSetting("TextSize", textsize); }
	onSnapgridChanged: { manager.setIntSetting("SnapGrid", snapgrid); }
	onToolChanged: { manager.setIntSetting("Tool", tool); }

	Component.onCompleted:
	{
		x = manager.getWindowPos().x
		y = manager.getWindowPos().y
		width = manager.getWindowSize().width
		height = manager.getWindowSize().height

		fillitem = manager.getIntSetting("FillItem")
		alignment = manager.getIntSetting("Alignment")
		linewidth = manager.getIntSetting("LineWidth")
		textsize = manager.getIntSetting("TextSize")
		snapgrid = manager.getIntSetting("SnapGrid")
		tool = manager.getIntSetting("Tool")

		filllist.setFill()
		snaplist.setSnap()
		sizelist.setSize()
		widthlist.setWidth()
		alignlist.setAlign()

		symbol = manager.getSymbol()

		visible = true
		manager.setInitialized()
	}

	function open()
	{

	}

	function save()
	{

	}

	function zoom(dir)
	{
		if ( dir === 0 )	// all
			zoomscale = 1.0
		else if ( dir > 0 )		// in
		{
			if ( (zoomscale *= zoomstep) > 1.0 )
				zoomscale = 1.0
		}
		else	// out
		{
			if ( (zoomscale /= zoomstep) < 0.1 )
				zoomscale = 0.1
		}
		editor.update()
	}

	function grid()
	{
		viewgrid = !viewgrid
		editor.update()
	}

	function undo(undo)
	{
		if ( manager.undo(undo) )
		{
			symbol = manager.getSymbol()
			editor.update()
		}
	}

	function cut()
	{
		manager.cutClipboard();
		symbol = manager.getSymbol()
		editor.update()
	}

	function copy()
	{
		manager.copyClipboard();
	}

	function paste()
	{
		manager.pasteClipboard();
		symbol = manager.getSymbol()
		editor.update()
	}

	function rotate(dir)
	{
		manager.rotateSymbol(dir)
		symbol = manager.getSymbol()
		editor.update()
	}

	function raise(dir)
	{
		manager.raiseItem(dir)
		symbol = manager.getSymbol()
		editor.update()
	}

	function remove()
	{
		manager.removeItem()
		symbol = manager.getSymbol()
		editor.update()
	}

	function help()
	{

	}

	function about()
	{

	}
}
