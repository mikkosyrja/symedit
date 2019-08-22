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

Parametrit: sijainti x,y (``U10,10``)

**D** - Piirrä viiva
^^^^^^^^^^^^^^^^^^^^

Piirtää viivan edellisestä sijainnista parametrin koordinaatteihin.

Parametrit: sijainti x,y (``U20,20``)

**R** - Piirrä ympyrä
^^^^^^^^^^^^^^^^^^^^^

Piirtää parametrin säteisen ympyrän käyttäen edellistä sijaintia keskipisteenä.

Parametrit: säde (``R30``)

**B** - Piirrä suorakaide
^^^^^^^^^^^^^^^^^^^^^^^^^

Piirtää suorakaiteen käyttäen edellistä sijantia ja parametrin koordinaatteja kulmina.

Parametrit: sijainti x,y (``B40,40``)

**C** - Väri-indeksi
^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin piirron väri-ideksiksi. Voimassa kunnes muutetaan.

Parametrit: väri-indeksi (``C3``)

**F** - Alueen täyttö
^^^^^^^^^^^^^^^^^^^^^

Asettaa alueen täytöksi jonkin seuraavan tyypin:

0. Ei täyttöä
1. Alueen täyttö taustavärillä
2. Alueen täyttö nykyisellä värillä

Alueen täyttö toimii suorakaiteen ja ympyrän kanssa. Reunaviiva piirretään vain, jos täyttö on nolla. Voimassa kunnes muutetaan.

Parametrit: täyttötyyppi (``F2``)

**G** - Tekstin kulma
^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kulmaksi gooneina. Vaakasuoran tekstin kulma on nolla ja kiertosuunta on vastapäivään. Voimassa kunnes muutetaan.

Parametrit: kulma (``G50``)

**J** - Tekstin asemointi
^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin asemoinniksi (1-12). Oletus on 9 (vasen alakulma). Voimassa kunnes muutetaan.

Parametrit: asemointi (``J9``)

**S** - Tekstin absoluuttinen koko
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kooksi millimetreinä (positiivinen) tai metreinä (negatiivinen). Oletus nolla käyttää sovelluksen asetuksia. Voimassa kunnes muutetaan.

Parametrit: koko (``S2.5``)

**P** - Tekstin suhteellinen koko
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kooksi prosentteina symbolin koosta. Oletus nolla käyttää sovelluksen asetuksia. Voimassa kunnes muutetaan.

Parametrit: prosentti (``P50``)
