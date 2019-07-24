.. _symbol-format-label:

Symbolin formaatti
==================

Formaatti koostuu puolipisteellä erotetuista piirtokomennoista. Symbolin koordinaattialue on kooltaan 100x100 ja origo on keskellä. Koordinaatiston X on vaakasuora komponentti vasemmalta oikealle ja Y on pystysuora komponentti alhaalta ylös. Kulmien nollasuunta on oikealle ja kiertosuunta vastapäivään.

Esimerkiksi ohjelman logona oleva hiusristikko määritellään seuraavasti:

``R50;U-50,0;D50,0;U0,50;D0,-50``

Komennot
--------

Käytettävissä ovat seuraavat piirtokomennot.

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

Asettaa parametrin piirron väri-ideksiksi. Voimassa kunnes muutetaan.

Parametrit: I (``C3``)

**F** - Aseta alueen täyttö
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa alueen täytöksi jonkin seuraavan tyypin:

0. Ei täyttöä
1. Alueen täyttö taustavärillä
2. Alueen täyttö nykyisellä värillä

Alueen täyttö toimii suorakaiteen ja ympyrän kanssa. Reunaviiva piirretään vain, jos täyttö on nolla. Voimassa kunnes muutetaan.

Parametrit: I (``F2``)

**G** - Aseta tekstin kulma
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kulmaksi gooneina. Vaakasuoran tekstin kulma on nolla ja kiertosuunta on vastapäivään. Voimassa kunnes muutetaan.

Parametrit: I (``G50``)

**J** - Aseta tekstin asemointi
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin asemoinniksi (1-12). Oletus on 9 (vasen alakulma). Voimassa kunnes muutetaan.

Parametrit: I (``J9``)
