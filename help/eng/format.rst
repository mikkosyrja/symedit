.. _symbol-format-label:

Symbol format
=============

Format contains drawing commands separated by semicolons. Symbol coordinate area is 100x100 and origin is at center. Coordinate X component is horizontal from left to right and Y component is vertical from bottom to top. Angle zero direction points to right and rotation is counter-clockwise.

For example, application crosshair logo can be defined like this:

``R50;U-50,0;D50,0;U0,50;D0,-50``

Commands
--------

Following drawing commads are available.

**U** - Change position
^^^^^^^^^^^^^^^^^^^^^^^

Changes current position to parameter coordinates.

Parameters: position x,y (``U10,10``)

**D** - Draw line
^^^^^^^^^^^^^^^^^

Draws line from previous position to parameter coordinates.

Parameters: position x,y (``U20,20``)

**R** - Draw circle
^^^^^^^^^^^^^^^^^^^

Draws parameter radius circle using previous position as center.

Parameters: radius (``R30``)

**B** - Draw rectangle
^^^^^^^^^^^^^^^^^^^^^^

Draws rectangle using previous position and parameter coordinates as corners.

Parameters: positin x,y (``B40,40``)

**C** - Color index
^^^^^^^^^^^^^^^^^^^

Sets parameter to current drawing color index. Affects until changed.

Parameters: color index (``C3``)

**F** - Area fill type
^^^^^^^^^^^^^^^^^^^^^^

Sets area fill type index to one of the following values:

0. No fill
1. Area fill using background color
2. Area fill using current color

Fill type works with rectangle and circle commands. Border is drawn only when the fill type is zero. Affects until changed.

Parameters: fill type (``F2``)

**G** - Text angle
^^^^^^^^^^^^^^^^^^

Sets parameter to text angle as gons. Horizontal text angle is zero and rotation is counter-clockwise. Affects until changed.

Parameters: angle (``G50``)

**J** - Text alignment
^^^^^^^^^^^^^^^^^^^^^^

Sets parameter to text alignment (1-12). Default is 9 (bottom left corner). Affects until changed.

Parameters: alignment (``J9``)

**S** - Text absolute size
^^^^^^^^^^^^^^^^^^^^^^^^^^

Sets parameter to text size as millimeters (positive) or meters (negative). Default zero uses application settings. Affects until changed.

Parameters: size (``S2.5``)

**P** - Text relative size
^^^^^^^^^^^^^^^^^^^^^^^^^^

Sets parameter to text size as a percentage of symbol size. Default zero uses application settings. Affects until changed.

Parameters: percentage (``P50``)
