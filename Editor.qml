import QtQuick 2.9

Rectangle
{
	enum Tool
	{
		Select = 1,
		Line = 11,
		RectCenter = 21,
		RectCorner = 22,
		CircleCorner = 31,
		CircleRadius = 32,
		CircleCenter = 33,
		ArcSemi = 41,
		ArcQuarter = 42,
		Text = 51
	}

	enum Operation
	{
		Line = 68,		// D
		Rectangle = 66,	// B
		Circle = 82		// R
	}

	property int units: 100
	property int max: units / 2
	property int grid: 10
	property int offset: 5
	property int total: units + offset * 2

	property bool horizontal: (height < width)
	property real scalexy: (horizontal ? height / total : width / total) * zoomscale

	property int startx: 0
	property int starty: 0
	property bool down: false
	property int endx: 0
	property int endy: 0

	anchors.fill: parent

	MouseArea
	{
		anchors.fill: parent
		hoverEnabled: true

		onPositionChanged:
		{
			mousex = Math.round((mouse.x - canvas.x) / scalexy / snapgrid) * snapgrid - max - offset
			mousey = max - Math.round((mouse.y - canvas.y) / scalexy / snapgrid) * snapgrid + offset

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

		onPressed:
		{
			startx = mousex
			starty = mousey
			manager.setActiveIndex(-1);
			down = true
		}

		onReleased:
		{
			if ( tool === Editor.Tool.Select )
			{
				manager.selectItem(Qt.point(mousex, mousey))
				canvas.requestPaint()
			}
			else
			{
				endx = mousex
				endy = mousey
				if ( startx != endx && starty != endy )
				{
					if ( tool === Editor.Tool.Line )
					{
						manager.addPointItem(Editor.Operation.Line, Qt.point(startx, starty), Qt.point(endx, endy), false)
						symbol = manager.getSymbol()
					}
					else if ( tool === Editor.Tool.RectCenter || tool === Editor.Tool.RectCorner )
					{
						if ( tool === Editor.Tool.RectCenter )
						{
							startx -= (endx - startx)
							starty -= (endy - starty)
						}
						manager.addPointItem(Editor.Operation.Rectangle, Qt.point(startx, starty), Qt.point(endx, endy), fillitem)
						symbol = manager.getSymbol()
					}
					else if ( tool > 30 && tool < 40 )	// circle
					{
						var deltax = Math.abs(mousex - startx)
						var deltay = Math.abs(mousey - starty)
						var centerx, centery, radius
						if ( tool === Editor.Tool.CircleCorner )
						{
							radius = (deltax < deltay ? deltax : deltay) / 2
							centerx = (startx + endx) / 2
							centery = (starty + endy) / 2
						}
						else if ( tool === Editor.Tool.CircleRadius )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay) / 2
							centerx = (startx + endx) / 2
							centery = (starty + endy) / 2
						}
						else if ( tool === Editor.Tool.CircleCenter )
						{
							radius = Math.sqrt(deltax * deltax + deltay * deltay)
							centerx = startx
							centery = starty
						}
						manager.addValueItem(Editor.Operation.Circle, Qt.point(centerx, centery), radius, fillitem)
						symbol = manager.getSymbol()
					}
				}
			}
			down = false
		}
	}

	Canvas
	{
		id: canvas

		width: total * scalexy; height: total * scalexy
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

		function paintline(context, start, end)
		{
			context.beginPath().moveTo((start.x + max + offset) * scalexy, (max - start.y + offset) * scalexy)
			context.lineTo((end.x + max + offset) * scalexy, (max - end.y + offset) * scalexy).stroke()
		}

		function paintrect(context, start, size, fill)
		{
			context.beginPath().rect((start.x + max + offset) * scalexy, (max - start.y + offset) * scalexy,
				size.width * scalexy, size.height * scalexy)
			if ( fill )
			{
				context.fillStyle = (fill === 1 ? "black" : "white")
				context.fill()
			}
			else
				context.stroke()
		}

		function paintcircle(context, center, radius, fill)
		{
			context.beginPath().ellipse((center.x + max - radius + offset) * scalexy,
				(max - center.y - radius + offset) * scalexy, radius * 2 * scalexy, radius * 2 * scalexy)
			if ( fill )
			{
				context.fillStyle = (fill === 1 ? "black" : "white")
				context.fill()
			}
			else
				context.stroke()
		}

		function paintgrid(context)
		{
			context.lineWidth = 0.2
			context.strokeStyle = "gray"
			context.fillStyle = "white"

			paintrect(context, Qt.point(-max - offset, max + offset), Qt.size(total, total), true)

			if ( viewgrid )
			{
				var row, col;
				for ( row = -max; row <= max; row += grid )
					paintline(context, Qt.point(-max, row), Qt.point(max, row))
				for ( col = -max; col <= max; col += grid )
					paintline(context, Qt.point(col, -max), Qt.point(col, max))

				context.lineWidth = 1
				paintline(context, Qt.point(0, -max), Qt.point(0, max))
				paintline(context, Qt.point(-max, 0), Qt.point(max, 0))

				paintrect(context, Qt.point(-max, max), Qt.size(units, units), false)
			}
		}

		function paintsymbol(context)
		{
			context.lineWidth = linewidth

			var active = manager.getActiveIndex();
			var index, count = manager.getItemCount()
			for ( index = 0; index < count; index++ )
			{
				context.strokeStyle = (index === active ? "red" : "black")

				var operation = manager.getItemOperation(index)
				var point, position = manager.getItemPosition(index)
				var fill = manager.getItemFill(index)
				if ( operation === Editor.Operation.Line )
				{
					point = manager.getItemPoint(index)
					paintline(context, position, point)
				}
				else if ( operation === Editor.Operation.Rectangle )
				{
					point = manager.getItemPoint(index)
					var deltax = point.x - position.x
					var deltay = position.y - point.y
					paintrect(context, position, Qt.size(deltax, deltay), fill)
				}
				else if ( operation === Editor.Operation.Circle )
				{
					var radius = manager.getItemValue(index)
					paintcircle(context, position, radius, fill)
				}
			}
		}

		onPaint:
		{
			var context = getContext("2d")

			paintgrid(context)

			context.strokeStyle = "black"
//			context.fillStyle = "black"

			paintsymbol(context)

			if ( down )
			{
				context.strokeStyle = "red"
				context.fillStyle = "red"

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
				}
				else if ( tool > 30 && tool < 40 )	// circle
				{
					var centerx, centery, radius
					if ( tool === Editor.Tool.CircleCorner )
					{
						radius = (deltax < deltay ? deltax : deltay) / 2
						centerx = (startx + mousex) / 2
						centery = (starty + mousey) / 2
					}
					else if ( tool === Editor.Tool.CircleRadius )
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
					if ( radius )
					{
						var center = Qt.point(centerx, centery)
						paintcircle(context, center, radius, fillitem)
					}
				}
				else if ( tool > 40 && tool < 50 )	// text
				{
					if ( tool === Editor.Tool.Texts )
					{
						//##
					}
				}
			}
		}
	}

	function update()
	{
		canvas.requestPaint()
	}
}
