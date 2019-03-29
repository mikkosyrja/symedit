Application usage
=================

xxx

Command line
------------

Usage: ``symedit [options] file``

-t, --transfer
^^^^^^^^^^^^^^

Given argument file name is a transfer file. When application exits, current symbol is automatically saved to this file.

-s, --symbol <symbol>
^^^^^^^^^^^^^^^^^^^^^

Reads symbol definition. For example: ``symedit -s R50;U0,50;D0,-50;U-50,0;D50,0``. See :ref:`symbol-format-label`.

-l, --language <lang>
^^^^^^^^^^^^^^^^^^^^^

Selects application language. Supported languages are english (eng) and finnish (fin). For example: ``symedit -l eng``

-h, --help
^^^^^^^^^^

Displays command line help.

file
^^^^

Symbol file name. Symbol file is simple text file containing symbol definition.

User interface
--------------

xxx

Menu
^^^^

See :doc:`menu`.


Toolbar
^^^^^^^

Toolbar upper line contains buttons for menu functions. Second line contains application drawing and user interface settings. Third line contains settings stored with edited symbol.

See :doc:`tools`.

Editor
^^^^^^

xxx

Statusbar
^^^^^^^^^

Bottom status bar shows mouse coordinates at left and symbol textual representation at right. Representation is same as format used for saving symbol to text file, but the active item definition is highlighted.
