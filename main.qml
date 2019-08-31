import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

import Qt.labs.platform 1.1 as Labs

ApplicationWindow
{
	property int mousex: 0
	property int mousey: 0

	property bool preview: false
	property bool viewgrid: true
	property real zoommax: 1.5
	property real zoommin: 0.1
	property real zoomscale: 1.5
	property real zoomstep: 1.3

	property int snapgrid: 1
	property real linewidth: 1
	property real symbolsize: 5.0
	property string language: "eng"

	property int colorindex: 1
	property int fillitem: 0
	property int alignment: 1
	property real textsize: 2.5
	property int sizeunit: 0

	property string textvalue: textfield.text
	property int tool: 0

	property string symbol
	property var popup: null

	id: window
	visible: false
	title: qsTrId("id_application_title")

	menuBar: MenuBar
	{
		Menu
		{
			//: file menu
			title: qsTrId("id_menu_file")
			MenuItem { text: qsTrId("id_menu_file_open"); shortcut: "Ctrl+O"; onTriggered: open() }
			MenuItem { text: qsTrId("id_menu_file_save"); shortcut: "Ctrl+S"; onTriggered: save(false) }
			MenuItem { text: qsTrId("id_menu_file_save_as"); shortcut: "Ctrl+Shift+S"; onTriggered: save(true) }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_file_exit"); shortcut: "Alt+F4"; onTriggered: Qt.quit() }
		}
		Menu
		{
			//: edit menu
			title: qsTrId("id_menu_edit")
			MenuItem { text: qsTrId("id_menu_edit_undo"); shortcut: "Ctrl+Z"; onTriggered: undo(true) }
			MenuItem { text: qsTrId("id_menu_edit_redo"); shortcut: "Ctrl+Y"; onTriggered: undo(false) }
//			MenuItem { text: qsTrId("id_menu_edit_redo"); shortcut: "Ctrl+Y,Ctrl+Shift+Z"; onTriggered: undo(false) }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_edit_cut"); shortcut: "Ctrl+X"; onTriggered: cutsymbol() }
			MenuItem { text: qsTrId("id_menu_edit_copy"); shortcut: "Ctrl+C"; onTriggered: copysymbol() }
			MenuItem { text: qsTrId("id_menu_edit_paste"); shortcut: "Ctrl+V"; onTriggered: pastesymbol() }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_edit_rotate_right"); shortcut: "Alt+Right"; onTriggered: rotatesymbol(1) }
			MenuItem { text: qsTrId("id_menu_edit_rotate_left"); shortcut: "Alt+Left"; onTriggered: rotatesymbol(-1) }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_edit_raise_item"); shortcut: "Alt+Up"; onTriggered: raiseitem(1) }
			MenuItem { text: qsTrId("id_menu_edit_lower_item"); shortcut: "Alt+Down"; onTriggered: raiseitem(-1) }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_edit_delete_item"); shortcut: "Delete"; onTriggered: removeitem() }
		}
		Menu
		{
			title: qsTrId("id_menu_view")
			MenuItem { text: qsTrId("id_menu_view_zoom_in"); shortcut: "Ctrl++"; onTriggered: zoom(1) }
			MenuItem { text: qsTrId("id_menu_view_zoom_out"); shortcut: "Ctrl+-"; onTriggered: zoom(-1) }
			MenuItem { text: qsTrId("id_menu_view_zoom_all"); shortcut: "Ctrl+0"; onTriggered: zoom(0) }
			MenuSeparator { }
			MenuItem
			{
				text: qsTrId("id_menu_view_grid"); shortcut: "Ctrl+G"
				checkable : true; checked: viewgrid
				onTriggered: grid()
			}
			MenuItem
			{
				text: qsTrId("id_menu_view_preview"); shortcut: "Ctrl+P"
				checkable : true; checked: preview
				onTriggered: previewsymbol()
			}
		}
		Menu
		{
			title: qsTrId("id_menu_tool")
			MenuTool { text: qsTrId("id_menu_tool_select"); tool: Editor.Tool.Select }
			MenuSeparator { }
			MenuTool { text: qsTrId("id_menu_tool_line"); tool: Editor.Tool.Line }
			MenuSeparator { }
			MenuTool { text: qsTrId("id_menu_tool_rect_corner"); tool: Editor.Tool.RectCorner }
			MenuTool { text: qsTrId("id_menu_tool_rect_center"); tool: Editor.Tool.RectCenter }
			MenuSeparator { }
			MenuTool { text: qsTrId("id_menu_tool_circle_corner"); tool: Editor.Tool.CircleCorner }
			MenuTool { text: qsTrId("id_menu_tool_circle_diameter"); tool: Editor.Tool.CircleDiameter }
			MenuTool { text: qsTrId("id_menu_tool_circle_center"); tool: Editor.Tool.CircleCenter }
/*
			MenuSeparator { }
			MenuTool { text: qsTrId("id_menu_tool_arc_semi"); tool: Editor.Tool.ArcSemi }
			MenuTool { text: qsTrId("id_menu_tool_arc_quarter"); tool: Editor.Tool.ArcQuarter }
*/
			MenuSeparator { }
			MenuTool { text: qsTrId("id_menu_tool_text_horizontal"); tool: Editor.Tool.TextHorizontal }
			MenuTool { text: qsTrId("id_menu_tool_text_rotated"); tool: Editor.Tool.TextRotated }
		}
		Menu
		{
			title: qsTrId("id_menu_settings")
			Menu
			{
				title: qsTrId("id_menu_settings_lang")
				MenuItem
				{
					text: qsTrId("id_menu_settings_eng")
					checkable : true; checked: language === "eng"
					onTriggered: setlanguage("eng")
				}
				MenuItem
				{
					text: qsTrId("id_menu_settings_fin")
					checkable : true; checked: language === "fin"
					onTriggered: setlanguage("fin")
				}
			}
		}
		Menu
		{
			title: qsTrId("id_menu_help")
			MenuItem { text: qsTrId("id_menu_help_contents"); shortcut: "F1"; onTriggered: help() }
			MenuSeparator { }
			MenuItem { text: qsTrId("id_menu_help_about"); onTriggered: aboutdialog.open() }
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
//				BarTool { image: "image/open_icon48.png"; tooltip: qsTrId("id_tooltip_file_open"); onClicked: open() }
//				BarTool { image: "image/save_icon48.png"; tooltip: qsTrId("id_tooltip_file_save"); onClicked: save(false) }
//				BarTool { image: "image/save_as.png"; tooltip: qsTrId("id_tooltip_file_save_as"); onClicked: save(true) }
//				BarSeparator { }
				BarTool { image: "image/undo_icon48.png"; tooltip: qsTrId("id_tooltip_edit_undo"); onClicked: undo(true) }
				BarTool { image: "image/redo_icon48.png"; tooltip: qsTrId("id_tooltip_edit_redo"); onClicked: undo(false) }
				BarTool { image: "image/cut_icon48.png"; tooltip: qsTrId("id_tooltip_edit_cut"); onClicked: cutsymbol() }
				BarTool { image: "image/copy_icon48.png"; tooltip: qsTrId("id_tooltip_edit_copy"); onClicked: copysymbol() }
				BarTool { image: "image/paste_icon48.png"; tooltip: qsTrId("id_tooltip_edit_paste"); onClicked: pastesymbol() }
				BarSeparator { }
				BarTool { image: "image/rotate_right.png"; tooltip: qsTrId("id_tooltip_edit_rotate_right"); onClicked: rotatesymbol(1) }
				BarTool { image: "image/rotate_left.png"; tooltip: qsTrId("id_tooltip_edit_rotate_left"); onClicked: rotatesymbol(-1) }
				BarTool { image: "image/up_icon48.png"; tooltip: qsTrId("id_tooltip_edit_raise_item"); onClicked: raiseitem(1) }
				BarTool { image: "image/down_icon48.png"; tooltip: qsTrId("id_tooltip_edit_lower_item"); onClicked: raiseitem(-1) }
				BarTool { image: "image/delete.png"; tooltip: qsTrId("id_tooltip_delete_item"); onClicked: removeitem() }
				BarSeparator { }
//				BarTool { image: "image/plus_icon48.png"; tooltip: qsTrId("id_tooltip_zoom_in"); onClicked: zoom(1) }
//				BarTool { image: "image/minus_icon48.png"; tooltip: qsTrId("id_tooltip_zoom_out"); onClicked: zoom(-1) }
				BarTool { image: "image/zoom_icon48.png"; tooltip: qsTrId("id_tooltip_zoom_all"); onClicked: zoom(0) }
				BarTool
				{
					image: "image/eye_icon48.png";
					tooltip: qsTrId("id_tooltip_zoom_preview");
					checkable: true
					checked: preview
					onClicked:
					{
						previewsymbol()	// clicking button seems to break binding
						checked = Qt.binding(function() { return preview })
					}
				}
				BarSeparator { }
				BarTool { image: "image/cursor_icon48.png"; tooltip: qsTrId("id_tooltip_tool_select"); tool: Editor.Tool.Select }
				BarSeparator { }
				BarTool { image: "image/polyline.png"; tooltip: qsTrId("id_tooltip_tool_line"); tool: Editor.Tool.Line }
				BarSeparator { }
				BarTool { image: "image/rectangle_corner.png"; tooltip: qsTrId("id_tooltip_tool_rect_corner"); tool: Editor.Tool.RectCorner }
				BarTool { image: "image/rectangle_center.png"; tooltip: qsTrId("id_tooltip_tool_rect_center"); tool: Editor.Tool.RectCenter }
				BarSeparator { }
				BarTool { image: "image/circle_corner.png"; tooltip: qsTrId("id_tooltip_tool_circle_corner"); tool: Editor.Tool.CircleCorner }
				BarTool { image: "image/circle_diameter.png"; tooltip: qsTrId("id_tooltip_tool_circle_diameter"); tool: Editor.Tool.CircleDiameter }
				BarTool { image: "image/circle_center.png"; tooltip: qsTrId("id_tooltip_tool_circle_center"); tool: Editor.Tool.CircleCenter }
/*
				BarSeparator { }
				BarTool { image: "image/semi_diameter.png"; tooltip: qsTrId("id_tooltip_tool_semi_diameter"); tool: Editor.Tool.ArcSemi }
				BarTool { image: "image/quarter_radius.png"; tooltip: qsTrId("id_tooltip_tool_quarter_radius"); tool: Editor.Tool.ArcQuarter }
*/
				BarSeparator { }
				BarTool { image: "image/text_horizontal.png"; tooltip: qsTrId("id_tooltip_tool_text_horizontal"); tool: Editor.Tool.TextHorizontal }
				BarTool { image: "image/text_rotated.png"; tooltip: qsTrId("id_tooltip_tool_text_rotated"); tool: Editor.Tool.TextRotated }
			}
			RowLayout
			{
				height: snaplist.height * 1.5
				Text { text: qsTrId("id_toolbar_application_settings") }
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_snap_grid") }
				ComboBox
				{
					id: snaplist
					implicitWidth: 60
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
				Text { text: qsTrId("id_toolbar_line_width") }
				ComboBox
				{
					id: widthlist
					implicitWidth: 60
					model: [ 1, 2, 3, 4, 5 ]
					onCurrentIndexChanged: { linewidth = currentIndex + 1; editor.update() }
					function setWidth() { currentIndex = linewidth - 1 }
				}
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_symbol_size") }
				ComboBox
				{
					id: symbollist
					implicitWidth: 70
					model: [ "1.0", "2.0", "3.0", "4.0", "5.0", "6.0", "7.0", "8.0", "9.0", "10.0" ]
					onCurrentIndexChanged: { symbolsize = currentIndex + 1; editor.update() }
					function setSize() { currentIndex = symbolsize - 1 }
				}
			}
			RowLayout
			{
				height: colorlist.height * 1.5
				Text { text: qsTrId("id_toolbar_symbol_settings") }
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_color_index") }
				ComboBox
				{
					id: colorlist
					implicitWidth: 60
					model: [ qsTrId("id_toolbar_color_white"), qsTrId("id_toolbar_color_black"),
						qsTrId("id_toolbar_color_blue"), qsTrId("id_toolbar_color_red"),
						qsTrId("id_toolbar_color_green"), qsTrId("id_toolbar_color_yellow"),
						"6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" ]
					onCurrentIndexChanged: { colorindex = currentIndex; editor.update() }
					function setColor() { currentIndex = colorindex }
				}
				BarSeparator { }
				Item { Layout.fillWidth: true }
				Text { text: qsTrId("id_toolbar_fill_item") }
				ComboBox
				{
					id: filllist
					implicitWidth: 60
					model:
					[
						qsTrId("id_toolbar_fill_none"),
						qsTrId("id_toolbar_fill_back"),
						qsTrId("id_toolbar_fill_area")
					]
					onCurrentIndexChanged: { fillitem = currentIndex; editor.update() }
					function setFill() { currentIndex = fillitem }
				}
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_alignment") }
				ComboBox
				{
					id: alignlist
					implicitWidth: 70
					model:
					[
						qsTrId("id_toolbar_align_top_right"),
						qsTrId("id_toolbar_align_top_center"),
						qsTrId("id_toolbar_align_top_left"),
						qsTrId("id_toolbar_align_base_right"),
						qsTrId("id_toolbar_align_base_center"),
						qsTrId("id_toolbar_align_base_left"),
						qsTrId("id_toolbar_align_bottom_right"),
						qsTrId("id_toolbar_align_bottom_center"),
						qsTrId("id_toolbar_align_bottom_left"),
						qsTrId("id_toolbar_align_middle_right"),
						qsTrId("id_toolbar_align_middle_center"),
						qsTrId("id_toolbar_align_middle_left")
					]
					onCurrentIndexChanged: { alignment = currentIndex + 1 }
					function setAlign() { currentIndex = alignment - 1 }
				}
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_text_size") }
				ComboBox
				{
					id: sizelist
					implicitWidth: 70
					model: [ "0.0", "0.5", "1.0", "1.5", "2.0", "2.5", "3.0", "3.5", "4.0", "4.5", "5.0",
						"5.5", "6.0", "6.5", "7.0", "7.5", "8.0", "8.5", "9.0", "9.5", "10.0" ]
					onCurrentIndexChanged: { textsize = currentIndex / 2.0; editor.update() }
					function setSize() { currentIndex = textsize * 2 }
				}
				ComboBox
				{
					id: unitlist
					implicitWidth: 60
					model: [ "mm", "m", "%" ]
					onCurrentIndexChanged: { sizeunit = currentIndex; editor.update() }
					function setUnit() { currentIndex = sizeunit }
				}
				BarSeparator { }
				Text { text: qsTrId("id_toolbar_text_field") }
				TextField
				{
					id: textfield
					implicitWidth: 160
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
			Text { Layout.minimumWidth: 40; text: " X: " + mousex }
			Text {	Layout.minimumWidth: 40; text: " Y: " + mousey }
			Item { Layout.fillWidth: true }
			Text {	Layout.minimumWidth: 40; text: symbol }
		}
	}

	Labs.FileDialog
	{
		id: filedialog
		title: (fileMode === Labs.FileDialog.OpenFile ? qsTrId("id_dialog_open_file") : qsTrId("id_dialog_save_file"))
		nameFilters: [ qsTrId("id_dialog_symbol_files"), qsTrId("id_dialog_all_files") ]
		onAccepted:
		{
			if ( fileMode === Labs.FileDialog.OpenFile )
			{
				manager.open(file)
				symbol = manager.getSymbol(true)
			}
			else	// save
				manager.save(file)
			editor.update()
		}
	}

	Labs.MessageDialog
	{
		id: aboutdialog
		title: qsTrId("id_dialog_about")
		text: qsTrId("id_dialog_about_text") + "\n\n© 2019 Mikko Syrjä"
		buttons: Labs.MessageDialog.Ok
	}

	onXChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onYChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onWidthChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }
	onHeightChanged: { manager.setGeometry(Qt.point(x, y), Qt.size(width, height)) }

	onSnapgridChanged: { manager.setIntSetting("SnapGrid", snapgrid); editor.update() }
	onLinewidthChanged: { manager.setIntSetting("LineWidth", linewidth) }
	onSymbolsizeChanged: { manager.setRealSetting("SymbolSize", symbolsize) }
	onLanguageChanged: { manager.setTextSetting("Language", language) }

	onColorindexChanged: { manager.setIntSetting("ColorIndex", colorindex) }
	onFillitemChanged: { manager.setIntSetting("FillItem", fillitem) }
	onAlignmentChanged: { manager.setIntSetting("Alignment", alignment) }
	onTextsizeChanged: { manager.setRealSetting("TextSize", textsize); editor.update() }
	onSizeunitChanged: { manager.setIntSetting("SizeUnit", sizeunit) }

	onTextvalueChanged: { manager.setTextSetting("TextValue", textvalue) }
	onToolChanged: { manager.setIntSetting("Tool", tool) }

	Component.onCompleted:
	{
		x = manager.getWindowPos().x
		y = manager.getWindowPos().y
		width = manager.getWindowSize().width
		height = manager.getWindowSize().height

		snapgrid = manager.getIntSetting("SnapGrid")
		linewidth = manager.getIntSetting("LineWidth")
		symbolsize = manager.getRealSetting("SymbolSize")
		language = manager.getTextSetting("Language")

		colorindex = manager.getIntSetting("ColorIndex")
		fillitem = manager.getIntSetting("FillItem")
		alignment = manager.getIntSetting("Alignment")
		textsize = manager.getRealSetting("TextSize")
		sizeunit = manager.getIntSetting("SizeUnit")

		textfield.text = manager.getTextSetting("TextValue")
		tool = manager.getIntSetting("Tool")

		snaplist.setSnap()
		widthlist.setWidth()
		symbollist.setSize()
//		langlist.setLang()

		colorlist.setColor()
		filllist.setFill()
		alignlist.setAlign()
		sizelist.setSize()
		unitlist.setUnit()

		symbol = manager.getSymbol(true)

		visible = true
		manager.setInitialized()
	}

	function open()
	{
		filedialog.fileMode = Labs.FileDialog.OpenFile
		filedialog.folder = manager.getTextSetting("Directory")
		filedialog.open()
	}

	function save(ask)
	{
		if ( ask || !manager.hasFilename() )
		{
			filedialog.fileMode = Labs.FileDialog.SaveFile
			filedialog.folder = manager.getTextSetting("Directory")
//			filedialog.currentFile = manager.getFilename()
			filedialog.open()
		}
		else
			manager.save("")
	}

	function zoom(dir)
	{
		if ( dir === 0 )	// all
		{
			preview = false
			zoomscale = zoommax
		}
		else if ( dir > 0 )	// in
		{
			if ( (zoomscale *= zoomstep) > zoommax )
				zoomscale = zoommax
		}
		else	// out
		{
			if ( (zoomscale /= zoomstep) < zoommin )
				zoomscale = zoommin
		}
		editor.update()
	}

	function grid()
	{
		viewgrid = !viewgrid
		editor.update()
	}

	function previewsymbol()
	{
		preview = !preview
		editor.update()
	}

	function undo(undo)
	{
		if ( manager.undo(undo) )
		{
			symbol = manager.getSymbol(true)
			editor.update()
		}
	}

	function cutsymbol()
	{
		manager.cutClipboard();
		symbol = manager.getSymbol(true)
		editor.update()
	}

	function copysymbol()
	{
		manager.copyClipboard();
	}

	function pastesymbol()
	{
		manager.pasteClipboard();
		symbol = manager.getSymbol(true)
		editor.update()
	}

	function rotatesymbol(dir)
	{
		manager.rotateSymbol(dir)
		symbol = manager.getSymbol(true)
		editor.update()
	}

	function raiseitem(dir)
	{
		manager.raiseItem(dir)
		symbol = manager.getSymbol(true)
		editor.update()
	}

	function removeitem()
	{
		manager.removeItem()
		symbol = manager.getSymbol(true)
		editor.update()
	}

	function setlanguage(lang)
	{
		language = lang
	}

	function help()
	{
		manager.help("main")
	}
}
