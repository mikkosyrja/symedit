import QtQuick 2.9

Rectangle
{
	enum Tool
	{
		Select = 1,
		Line = 11,
		Polyline = 12,
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

	property int margin: 20
	property int units: 100
	property int max: units / 2
	property int grid: 10

	property bool horizontal: (height < width)
	property real scalexy: (horizontal ? (height - margin * 2) / units : (width - margin * 2) / units)

	property int mousex: 0
	property int mousey: 0

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
			mousex = Math.round((mouse.x - canvas.x) / scalexy / snap) * snap - max
			mousey = max - Math.round((mouse.y - canvas.y) / scalexy / snap) * snap

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
			if ( tool === Editor.Tool.Polyline )
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
			endx = mousex
			endy = mousey
			down = false
		}
	}

	Canvas
	{
		id: canvas

		width: units * scalexy; height:  units * scalexy
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

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

			context.beginPath().moveTo(0, max * scalexy)
			context.lineTo(units * scalexy, max * scalexy)
			context.closePath().stroke()

			context.beginPath().moveTo(max * scalexy, 0)
			context.lineTo(max * scalexy, units * scalexy)
			context.closePath().stroke()

			context.strokeRect(0, 0, units * scalexy, units * scalexy)
		}

		onPaint:
		{
			var context = getContext("2d")

			paintgrid(context)

			context.strokeStyle = "black"
			context.fillStyle = "black"
//			context.lineWidth = 2

			if ( down )
			{
				var cornerx = (mousex < startx ? mousex : startx)
				var cornery = (mousey > starty ? mousey : starty)
				var deltax = Math.abs(mousex - startx)
				var deltay = Math.abs(mousey - starty)
				if ( tool > 10 && tool < 20 )	// line
				{
					if ( tool === Editor.Tool.Line )
					{
						context.beginPath().moveTo((startx + max) * scalexy, (max - starty) * scalexy)
						context.lineTo((mousex + max) * scalexy, (max - mousey) * scalexy)
						context.closePath().stroke()
					}
					else if ( tool === Editor.Tool.Polyline )
					{
						context.beginPath().moveTo((startx + max) * scalexy, (max - starty) * scalexy)
						context.lineTo((mousex + max) * scalexy, (max - mousey) * scalexy)
						context.closePath().stroke()
					}
				}
				else if ( tool > 20 && tool < 30 )	// rectangle
				{
					if ( tool === Editor.Tool.RectangleCenter )
					{
						//##
					}
					else if ( tool === Editor.Tool.RectangleCorner )
					{
						context.rect((cornerx + max) * scalexy, (max - cornery) * scalexy,
							deltax * scalexy, deltay * scalexy)
					}
					if ( fill )
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
						context.ellipse((centerx + max - radius) * scalexy, (max - centery - radius) * scalexy,
							radius * 2 * scalexy, radius * 2 * scalexy)
						if ( fill )
							context.fill()
						else
							context.stroke()
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
