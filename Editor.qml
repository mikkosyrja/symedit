import QtQuick 2.9
import Org.Syrja.Symbol.Operation 1.0

Rectangle
{
	enum Tool
	{
		Select = 1,
		Line = 11,
		RectCenter = 21,
		RectCorner = 22,
		CircleCorner = 31,
		CircleDiameter = 32,
		CircleCenter = 33,
		ArcSemi = 41,
		ArcQuarter = 42,
		TextHorizontal = 51,
		TextRotated = 52
	}

	property int units: 100
	property int max: units / 2
	property int offsetx: 100
	property int offsety: 50
	property int totalx: units + offsetx * 2	// 300
	property int totaly: units + offsety * 2	// 200

	property bool horizontal: (height / 2 < width / 3)
	property real scalexy: (horizontal ? height / totaly : width / totalx) * (preview ? zoommin : zoomscale)

	property bool down: false
	property int startx: 0
	property int starty: 0
	property int endx: 0
	property int endy: 0

	property string paintcolor: "black"
	property string editcolor: "brown"
	property string gridcolor: "gray"
	property string backcolor: "white"
	property string graycolor: "lightgray"

	anchors.fill: parent
	color: graycolor

	MouseArea
	{
		anchors.fill: parent
		hoverEnabled: true

		onPositionChanged:
		{
			if ( tool === Editor.Tool.Select )
			{
				mousex = Math.round((mouse.x - canvas.x) / scalexy) - max - offsetx
				mousey = max - Math.round((mouse.y - canvas.y) / scalexy) + offsety
			}
			else	// snap and clip
			{
				mousex = Math.round((mouse.x - canvas.x) / scalexy / snapgrid) * snapgrid - max - offsetx
				mousey = max - Math.round((mouse.y - canvas.y) / scalexy / snapgrid) * snapgrid + offsety
				if ( mousex < -max)
					mousex = -max
				else if ( mousex > max )
					mousex = max
				if ( mousey < -max )
					mousey = -max
				else if ( mousey > max )
					mousey = max

				if ( down )
					canvas.requestPaint()
			}
		}

		onPressed:
		{
			startx = mousex
			starty = mousey
			manager.setActiveIndex(-1);
			focus = true
			down = true
		}

		onReleased:
		{
			down = false
			endx = mousex
			endy = mousey
			if ( tool === Editor.Tool.Select )
			{
				manager.selectItem(Qt.point(endx, endy))
				symbol = manager.getSymbol(true)
				canvas.requestPaint()
			}
			else if ( !preview )
			{
				if ( tool === Editor.Tool.TextHorizontal )
				{
					if ( manager.addTextItem(Operation.Text, Qt.point(endx, endy), Qt.point(endx, endy), textvalue, colorindex, alignment) )
					{
						symbol = manager.getSymbol(true)
						canvas.requestPaint()
					}
				}
				else if ( startx != endx || starty != endy )
				{
					if ( tool === Editor.Tool.Line )
					{
						manager.addLineItem(Operation.Line, Qt.point(startx, starty), Qt.point(endx, endy), 0, colorindex, 0)
						symbol = manager.getSymbol(true)
					}
					else if ( tool === Editor.Tool.RectCenter || tool === Editor.Tool.RectCorner )
					{
						if ( tool === Editor.Tool.RectCenter )
						{
							startx -= (endx - startx)
							starty -= (endy - starty)
						}
						if ( manager.addLineItem(Operation.Rectangle, Qt.point(startx, starty), Qt.point(endx, endy), 0, colorindex, fillitem) )
							symbol = manager.getSymbol(true)
					}
					else if ( tool > 30 && tool < 50 )	// circle or arc
					{
						var deltax = Math.abs(mousex - startx)
						var deltay = Math.abs(mousey - starty)
						var centerx, centery, radius
						if ( tool === Editor.Tool.CircleCorner )
						{
							radius = (deltax < deltay ? deltax : deltay) / 2
							centerx = (startx + endx) / 2
							centery = (starty + endy) / 2
							if ( manager.addPointItem(Operation.Circle, Qt.point(centerx, centery), radius, colorindex, fillitem) )
								symbol = manager.getSymbol(true)
						}
						else if ( tool === Editor.Tool.CircleDiameter )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay) / 2
							centerx = (startx + endx) / 2
							centery = (starty + endy) / 2
							if ( manager.addPointItem(Operation.Circle, Qt.point(centerx, centery), radius, colorindex, fillitem) )
								symbol = manager.getSymbol(true)
						}
						else if ( tool === Editor.Tool.CircleCenter )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay)
							if ( manager.addPointItem(Operation.Circle, Qt.point(startx, starty), radius, colorindex, fillitem) )
								symbol = manager.getSymbol(true)
						}
						else if ( tool === Editor.Tool.ArcSemi )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay) / 2
							if ( manager.addLineItem(Operation.Arc, Qt.point(startx, starty), Qt.point(endx, endy), radius, colorindex, fillitem) )
								symbol = manager.getSymbol(true)
						}
						else if ( tool === Editor.Tool.ArcQuarter )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay)
							//##
						}
					}
					else if ( tool === Editor.Tool.TextRotated )
					{
						if ( manager.addTextItem(Operation.Text, Qt.point(startx, starty), Qt.point(endx, endy), textvalue, colorindex, alignment) )
							symbol = manager.getSymbol(true)
					}
				}
				else	// activate last
				{
					manager.setActiveIndex(manager.getItemCount() - 1);
					canvas.requestPaint()
				}
			}
		}
	}

	Canvas
	{
		id: canvas

		width: totalx * scalexy; height: totaly * scalexy
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

		function paintline(context, start, end)
		{
			context.beginPath().moveTo((start.x + max + offsetx) * scalexy, (max - start.y + offsety) * scalexy)
			context.lineTo((end.x + max + offsetx) * scalexy, (max - end.y + offsety) * scalexy).stroke()
		}

		function paintrect(context, start, size, fill)
		{
			context.beginPath().rect((start.x + max + offsetx) * scalexy, (max - start.y + offsety) * scalexy,
				size.width * scalexy, size.height * scalexy)
			if ( fill )
			{
				context.fillStyle = (fill === 3 ? graycolor : (fill === 2 ? paintcolor : backcolor))
				context.fill()
			}
			else
				context.stroke()
		}

		function paintcircle(context, center, radius, fill)
		{
			context.beginPath().ellipse((center.x + max - radius + offsetx) * scalexy,
				(max - center.y - radius + offsety) * scalexy, radius * 2 * scalexy, radius * 2 * scalexy)
			if ( fill )
			{
				context.fillStyle = (fill === 2 ? paintcolor : backcolor)
				context.fill()
			}
			else
				context.stroke()
		}

		function paintsemicircle(context, start, end, radius, fill)
		{
//			context.beginPath().moveTo((start.x + max + offsetx) * scalexy, (max - start.y + offsety) * scalexy)
			context.beginPath().moveTo((0 + max + offsetx) * scalexy, (max - 0 + offsety) * scalexy)
			context.arcTo((start.x + max + offsetx) * scalexy, (max - start.y + offsety) * scalexy,
				(end.x + max + offsetx) * scalexy, (max - end.y + offsety) * scalexy, radius)
			if ( fill )
			{
				context.fillStyle = (fill === 2 ? paintcolor : backcolor)
				context.fill()
			}
			else
				context.stroke()
		}

		function setalignment(context, align)
		{
			switch ( align )
			{
				case 1:		context.textAlign = "right"; context.textBaseline = "top"; break
				case 2:		context.textAlign = "center"; context.textBaseline = "top"; break
				case 3:		context.textAlign = "left"; context.textBaseline = "top"; break
				case 4:		context.textAlign = "right"; context.textBaseline = "alphabetic"; break
				case 5:		context.textAlign = "center"; context.textBaseline = "alphabetic"; break
				case 6:		context.textAlign = "left"; context.textBaseline = "alphabetic"; break
				case 7:		context.textAlign = "right"; context.textBaseline = "bottom"; break
				case 8:		context.textAlign = "center"; context.textBaseline = "bottom"; break
				case 9:		context.textAlign = "left"; context.textBaseline = "bottom"; break
				case 10:	context.textAlign = "right"; context.textBaseline = "middle"; break
				case 11:	context.textAlign = "center"; context.textBaseline = "middle"; break
				case 12:	context.textAlign = "left"; context.textBaseline = "middle"; break
			}
		}

		function setcolorindex(context, color)
		{
			switch ( color )
			{
				case 0:		paintcolor = "white"; break
				case 1:		paintcolor = "black"; break
				case 2:		paintcolor = "blue"; break
				case 3:		paintcolor = "red"; break
				case 4:		paintcolor = "green"; break
				case 5:		paintcolor = "yellow"; break
				default:	paintcolor = "black"; break
			}
		}

		function painttext(context, string, point, end, active)
		{
			var currentwidth = context.lineWidth
			context.lineWidth = textsize * (preview ? zoommin : zoomscale) / 2
			var fontsize = 30 * textsize * (preview ? zoommin : zoomscale)
			context.font = fontsize.toString() + "px sans-serif"
			var position = Qt.point((point.x + max + offsetx) * scalexy, (max - point.y + offsety) * scalexy)
			context.translate(position.x, position.y)
			if ( point.x !== end.x || point.y !== end.y )	// rotate
				context.rotate(Math.atan2(point.y - end.y, end.x - point.x))
			context.fillText(string, 0, 0)
			context.strokeText(string, 0, 0)
			if ( !preview )		// attach point
			{
				if ( active )
					context.fillStyle = editcolor
				context.beginPath().ellipse(zoomscale * -5 , zoomscale * -5, zoomscale * 10, zoomscale * 10).fill()
				if ( active )
					context.fillStyle = paintcolor
			}
			context.resetTransform()
			context.lineWidth = currentwidth
		}

		function paintgrid(context)
		{
			context.lineWidth = 0.4
			context.strokeStyle = gridcolor
			if ( viewgrid && !preview )
			{
				var row, col;
				for ( row = -max; row <= max; row += snapgrid )
					paintline(context, Qt.point(-max, row), Qt.point(max, row))
				for ( col = -max; col <= max; col += snapgrid )
					paintline(context, Qt.point(col, -max), Qt.point(col, max))

				context.lineWidth = 1
				paintline(context, Qt.point(0, -max), Qt.point(0, max))
				paintline(context, Qt.point(-max, 0), Qt.point(max, 0))

				paintrect(context, Qt.point(-max, max), Qt.size(units, units), 0)
			}
		}

		function paintsymbol(context)
		{
			setcolorindex(context, 1)
			context.lineWidth = linewidth * (preview ? zoommin * 2 : zoomscale) * 2

			var currentcolor = 1
			var active = manager.getActiveIndex()
			var count = manager.getItemCount()
			var operation, index, radius, fill, color
			var point, position
			for ( index = 0; index < count; index++ )
			{
				operation = manager.getItemOperation(index)
				position = manager.getItemPosition(index)
				fill = manager.getItemFill(index)
				color = manager.getItemColor(index)
				if ( color !== currentcolor )
				{
					setcolorindex(context, color)
					currentcolor = color
				}
				context.strokeStyle = (index === active && !preview ? editcolor : paintcolor)
				context.fillStyle = paintcolor

				if ( operation === Operation.Line )
				{
					point = manager.getItemPoint(index)
					paintline(context, position, point)
				}
				else if ( operation === Operation.Rectangle )
				{
					point = manager.getItemPoint(index)
					var deltax = point.x - position.x
					var deltay = position.y - point.y
					paintrect(context, position, Qt.size(deltax, deltay), fill)
					if ( !preview && fill && index === active )
						paintrect(context, position, Qt.size(deltax, deltay), 0)
				}
				else if ( operation === Operation.Circle )
				{
					radius = manager.getItemValue(index)
					paintcircle(context, position, radius, fill)
					if ( !preview && fill && index === active )
						paintcircle(context, position, radius, false)
				}
				else if ( operation === Operation.Arc )
				{
					point = manager.getItemPoint(index)
					radius = manager.getItemValue(index)
					paintsemicircle(context, position, point, radius, fill)
					if ( !preview && fill && index === active )
						paintsemicircle(context, position, point, radius, false)
				}
				else if ( operation === Operation.Text )
				{
					point = manager.getItemPoint(index)
					setalignment(context, manager.getItemAlign(index))
					painttext(context, manager.getItemText(index), position, point, index === active)
				}
			}
		}

		onPaint:
		{
			var context = getContext("2d")
			context.lineCap = "round"

			paintrect(context, Qt.point(-max - offsetx, max + offsety), Qt.size(totalx, totaly), 3)
			paintsymbol(context)

			if ( down )
			{
				setcolorindex(context, colorindex)
				context.strokeStyle = editcolor
				context.fillStyle = paintcolor

				var cornerx = (mousex < startx ? mousex : startx)
				var cornery = (mousey > starty ? mousey : starty)
				var deltax = Math.abs(mousex - startx)
				var deltay = Math.abs(mousey - starty)
				var start = Qt.point(startx, starty)
				var end = Qt.point(mousex, mousey)
				if ( tool > 10 && tool < 20 )	// line
				{
					if ( tool === Editor.Tool.Line )
						paintline(context, start, end)
				}
				else if ( tool > 20 && tool < 30 )	// rectangle
				{
					if ( tool === Editor.Tool.RectCenter )
					{
						cornerx = startx + (mousex < startx ? -deltax : -deltax)
						cornery = starty + (mousey < starty ? deltay : deltay)
						deltax *= 2; deltay *= 2
					}
					paintrect(context, Qt.point(cornerx, cornery), Qt.size(deltax, deltay), fillitem)
					if ( fillitem )
						paintrect(context, Qt.point(cornerx, cornery), Qt.size(deltax, deltay), 0)
				}
				else if ( tool > 30 && tool < 50 )	// circle or arc
				{
					var centerx, centery, radius
					if ( tool === Editor.Tool.CircleCorner )
					{
						radius = (deltax < deltay ? deltax : deltay) / 2
						centerx = (startx + mousex) / 2
						centery = (starty + mousey) / 2
					}
					else if ( tool === Editor.Tool.CircleDiameter )
					{
						radius = Math.sqrt(deltax * deltax + deltay * deltay) / 2
						centerx = (startx + mousex) / 2
						centery = (starty + mousey) / 2
					}
					else if ( tool === Editor.Tool.CircleCenter )
					{
						radius = Math.sqrt(deltax * deltax + deltay * deltay)
						centerx = startx
						centery = starty
					}
					else if ( tool === Editor.Tool.ArcSemi )
					{
						radius = Math.sqrt(deltax * deltax + deltay * deltay) / 2
						centerx = (startx + mousex) / 2
						centery = (starty + mousey) / 2
					}
					if ( radius )
					{
						var center = Qt.point(centerx, centery)
						if ( tool > 40 )
						{
							paintsemicircle(context, center, start, end, radius, fillitem)
//							if ( fillitem )
//								paintsemicircle(context, center, radius, false)
						}
						else
						{
							paintcircle(context, center, radius, fillitem)
							if ( fillitem )
								paintcircle(context, center, radius, false)
						}
					}
				}
				else if ( tool > 50 && tool < 60 )	// text
				{
					setalignment(context, alignment)
					if ( tool === Editor.Tool.TextHorizontal )
						painttext(context, textvalue, Qt.point(mousex, mousey), Qt.point(mousex, mousey), true)
					else if ( tool === Editor.Tool.TextRotated )
						painttext(context, textvalue, Qt.point(startx, starty), Qt.point(mousex, mousey), true)
				}
			}

			paintgrid(context)
		}
	}

	function update()
	{
		canvas.requestPaint()
	}
}
