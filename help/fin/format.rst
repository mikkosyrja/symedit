.. _symbol-format-label:

Symbolin formaatti
==================

xxx

Komennot
--------

Komennot erotetaan toisistaan puolipisteillä. Koordinaatiston X on vaakasuora komponentti vasemmalta oikealle ja Y on pystysuora komponentti alhaalta ylös.

**U** - Muuta sijaintia
^^^^^^^^^^^^^^^^^^^^^^^

Muuttaa nykyisen sijainnin parametrin koordinaatteihin.

Parametrit: X,Y (``U10,10``)

**D** - Piirrä viiva
^^^^^^^^^^^^^^^^^^^^

Piirtää viivan edellisestä sijainnista parametrin koordinaatteihin.

Parametrit: X,Y (``U20,20``)

**R** - Piirrä ympyrä
^^^^^^^^^^^^^^^^^^^^^

Piirtää parametrin säteisen ympyrän käyttäen edellistä sijaintia keskipisteenä.

Parametrit: R (``R30``)

**B** - Piirrä suorakaide
^^^^^^^^^^^^^^^^^^^^^^^^^

Piirtää suorakaiteen käyttäen edellistä sijantia ja parametrin koordinaatteja kulmina.

Parametrit: X,Y (``B40,40``)

**C** - Aseta väri-indeksi
^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin piirron väri-ideksiksi.

Parameters: I (``C3``)

**F** - Aseta alueen täyttö
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa alueen täytöksi jonkin seuraavan tyypin:

0. Ei täyttöä
1. Alueen täyttö taustavärillä
2. Alueen täyttö nykyisellä värillä

Alueen täyttö toimii suorakaiteen ja ympyrän kanssa. Reunaviiva piirretään vain, jos täyttö on nolla.

Parameters: I (``F2``)

