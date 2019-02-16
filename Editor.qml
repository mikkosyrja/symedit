import QtQuick 2.9

Rectangle
{
	enum Tool
	{
		Select = 1,
		LineSingle = 11,
		LinePoly = 12,
		RectangleCenter = 21,
		RectangleCorner = 22,
		CircleCenter = 31,
		CircleHorizontal = 32,
		CircleVertical = 33,
		CircleCorner = 34,
		ArcSemicircle = 41,
		ArcQuarter = 42,
		Text = 51
	}

	enum Operation
	{
		Move = 85,		// U
		Line = 68,		// D
		Radius = 82		// R
	}

	property int margin: 20
	property int units: 100
	property int max: units / 2
	property int grid: 10

	property bool horizontal: (height < width)
	property real scalexy: (horizontal ? (height - margin * 2) / units : (width - margin * 2) / units)

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
			mousex = Math.round((mouse.x - canvas.x) / scalexy / snapgrid) * snapgrid - max
			mousey = max - Math.round((mouse.y - canvas.y) / scalexy / snapgrid) * snapgrid

			if ( mouse.x < canvas.x )
				mousex = -max
			else if ( mouse.x > canvas.x + canvas.width )
				mousex = max
			if ( mouse.y < canvas.y )
				mousey = max
			else if ( mouse.y >= canvas.y + canvas.height )
				mousey = -max

			if ( down )
				canvas.requestPaint()
		}

		onPressed:
		{
			if ( tool === Editor.Tool.LinePoly )
			{
				startx = endx
				starty = endy
			}
			else
			{
				startx = mousex
				starty = mousey
			}
			down = true
		}

		onReleased:
		{
			if ( tool === Editor.Tool.Select )
			{
				var index = manager.selectItem(Qt.point(mousex, mousey))
			}
			else
			{
				endx = mousex
				endy = mousey
				down = false
			}
		}
	}

	Canvas
	{
		id: canvas

		width: units * scalexy; height:  units * scalexy
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

//		clip: false

		function paintline(context, start, end)
		{
			context.beginPath().moveTo((start.x + max) * scalexy, (max - start.y) * scalexy)
			context.lineTo((end.x + max) * scalexy, (max - end.y) * scalexy)
			context.closePath().stroke()
		}

		function paintcircle(context, center, radius, fill)
		{
			context.ellipse((center.x + max - radius) * scalexy, (max - center.y - radius) * scalexy,
				radius * 2 * scalexy, radius * 2 * scalexy)
			if ( fill )
				context.fill()
			else
				context.stroke()
		}

		function paintgrid(context)
		{
			context.lineWidth = 0.2
			context.strokeStyle = "gray"
			context.fillStyle = "white"

			context.fillRect(0, 0, units * scalexy, units * scalexy)

			var row, col;
			for ( row = 0; row <= units; row += grid )
			{
				context.beginPath().moveTo(0, row * scalexy)
				context.lineTo(units * scalexy, row * scalexy)
				context.closePath().stroke()
			}

			for ( col = 0; col <= units; col += grid )
			{
				context.beginPath().moveTo(col * scalexy, 0)
				context.lineTo(col * scalexy, units * scalexy)
				context.closePath().stroke()
			}

			context.lineWidth = 1
			paintline(context, Qt.point(0, -max), Qt.point(0, max))
			paintline(context, Qt.point(-max, 0), Qt.point(max, 0))

			context.strokeRect(0, 0, units * scalexy, units * scalexy)
		}

		function paintsymbol(context)
		{
			context.lineWidth = linewidth

			var previous = Qt.point(0, 0)
			var index, count = manager.getItemCount()
			for ( index = 0; index < count; index++ )
			{
				var operation = manager.getItemOperation(index)
				var position = manager.getItemPoint(index)
				var fill = manager.getItemFill(index)
				if ( operation === Editor.Operation.Move )
				{
					previous = position
				}
				else if ( operation === Editor.Operation.LineSingle )
				{
					paintline(context, previous, position)
					previous = position
				}
				else if ( operation === Editor.Operation.Radius )
				{
					var radius = position.x
					paintcircle(context, previous, radius, fill)
				}
			}
		}

		onPaint:
		{
			var context = getContext("2d")

			paintgrid(context)

			context.strokeStyle = "black"
			context.fillStyle = "black"

			paintsymbol(context)

			if ( down )
			{
				var cornerx = (mousex < startx ? mousex : startx)
				var cornery = (mousey > starty ? mousey : starty)
				var deltax = Math.abs(mousex - startx)
				var deltay = Math.abs(mousey - starty)
				var start = Qt.point(startx, starty)
				var end = Qt.point(mousex, mousey)
				if ( tool > 10 && tool < 20 )	// line
				{
					if ( tool === Editor.Tool.LineSingle )
						paintline(context, start, end)
					else if ( tool === Editor.Tool.Polyline )
					{
						paintline(context, start, end)	//##
					}
				}
				else if ( tool > 20 && tool < 30 )	// rectangle
				{
					if ( tool === Editor.Tool.RectangleCenter )
					{
						cornerx = startx + (mousex < startx ? -deltax : -deltax)
						cornery = starty + (mousey < starty ? deltay : deltay)
						deltax *= 2
						deltay *= 2
					}
					else if ( tool === Editor.Tool.RectangleCorner ) { }
					context.rect((cornerx + max) * scalexy, (max - cornery) * scalexy,
						deltax * scalexy, deltay * scalexy)
					if ( fillitem )
						context.fill()
					else
						context.stroke()
				}
				else if ( tool > 30 && tool < 40 )	// circle
				{
					var centerx, centery, radius
					if ( tool === Editor.Tool.CircleCenter )
					{
						radius = Math.sqrt(deltax * deltax + deltay * deltay)
						centerx = startx
						centery = starty
					}
					else if ( tool === Editor.Tool.CircleHorizontal )
					{
						radius = deltax / 2
						centerx = startx + (mousex < startx ? -radius : radius)
						centery = starty
					}
					else if ( tool === Editor.Tool.CircleVertical )
					{
						radius = deltay / 2
						centerx = startx
						centery = starty + (mousey < starty ? -radius : radius)
					}
					else if ( tool === Editor.Tool.CircleCorner )
					{
						radius = (deltax < deltay ? deltax : deltay) / 2
						centerx = cornerx + radius
						centery = cornery - radius
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
}
