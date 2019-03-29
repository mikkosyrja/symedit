.. _symbol-format-label:

Symbol format
=============

xxx

Commands
--------

Commands are separated by semicolons. Coordinate X is horizontal component from left to right and Y is vertical component from bottom to top.

**U** - Change position
^^^^^^^^^^^^^^^^^^^^^^^

Changes current position to parameter coordinates.

Parameters: X,Y (``U10,10``)

**D** - Draw line
^^^^^^^^^^^^^^^^^

Draws line from previous position to parameter coordinates.

Parameters: X,Y (``U20,20``)

**R** - Draw circle
^^^^^^^^^^^^^^^^^^^

Draws parameter radius circle using previous position as center.

Parameters: R (``R30``)

**B** - Draw rectangle
^^^^^^^^^^^^^^^^^^^^^^

Draws rectangle using previous position and parameter coordinates as corners.

Parameters: X,Y (``B40,40``)

**C** - Set color index
^^^^^^^^^^^^^^^^^^^^^^^

Sets parameter to current drawing color index.

Parameters: I (``C3``)

**F** - Set area fill type
^^^^^^^^^^^^^^^^^^^^^^^^^^

Sets area fill type index to one of the following values:

0. No fill
1. Area fill using background color
2. Area fill using current color

Fill type works with rectangle and circle commands. Border is drawn only when the fill type is zero.

Parameters: I (``F2``)

