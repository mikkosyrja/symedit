Ohjelman käyttö
===============

xxx

Komentorivi
-----------

Käyttö: ``symedit [options] file``

-t, --transfer
^^^^^^^^^^^^^^

Parametrina annettu tiedosto on siirtotiedosto. Kun ohjelma lopetetaan, editoitava symboli tallennetaan tähän tiedostoon automaattisesti.

-s, --symbol <symbol>
^^^^^^^^^^^^^^^^^^^^^

Lukee symbolin määrittelyn. Esimerkiksi: ``symedit -s R50;U0,50;D0,-50;U-50,0;D50,0``. Katso :ref:`symbol-format-label`.

-l, --language <lang>
^^^^^^^^^^^^^^^^^^^^^

Valitsee sovelluksen kielen. Tuettuja kieliä ovat englanti (eng) ja suomi (fin). Esimerkiksi: ``symedit -l fin``

-h, --help
^^^^^^^^^^

Näyttää komentorivin ohjeen.

file
^^^^

Symbolitiedoston nimi. Symbolitiedosto on tekstitiedosto, joka sisältää symbolin määrittelyn.

Käyttöliitymä
-------------

xxx

Valikko
^^^^^^^

Katso :doc:`menu`.


Työkalupalkki
^^^^^^^^^^^^^

Työkalupalkin ylimmällä rivillä ovat painikkeet valikon toiminnoille. Toisella rivillä on ohjelman piirron ja käyttöliittymän asetuksia. Kolmannella rivillä on symbolin mukana tallentuvia asetuksia.

Katso :doc:`tools`.

Editori
^^^^^^^

xxx

Tilarivi
^^^^^^^^

Alareunan tilarivi näyttää vasemmalla hiiren koordinaatit ja oikealla symbolin tekstimuotoisen esityksen. Muoto on sama, jossa symboli tallentuu tekstitiedostoon, mutta lisäksi aktiivisen kohteen määritys on korostettu.

