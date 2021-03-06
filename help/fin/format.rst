.. _symbol-format-label:

Symbolin formaatti
==================

Formaatti koostuu puolipisteellä erotetuista piirtokomennoista. Symbolin koordinaattialue on kooltaan 100x100 ja origo on keskellä. Koordinaatiston X on vaakasuora komponentti vasemmalta oikealle ja Y on pystysuora komponentti alhaalta ylös. Kulmien nollasuunta on oikealle ja kiertosuunta vastapäivään.

Esimerkiksi ohjelman logona oleva hiusristikko määritellään seuraavasti:

``R50;U-50,0;D50,0;U0,50;D0,-50``

Komennot
--------

Käytettävissä ovat seuraavat piirtokomennot.

**U** - Sijainti
^^^^^^^^^^^^^^^^

Muuttaa nykyisen sijainnin parametrin koordinaatteihin.

Parametrit: sijainti x,y (``U10,10``)

**D** - Viiva
^^^^^^^^^^^^^

Piirtää viivan edellisestä sijainnista parametrin koordinaatteihin.

Parametrit: sijainti x,y (``U20,20``)

**R** - Ympyrä
^^^^^^^^^^^^^^

Piirtää parametrin säteisen ympyrän käyttäen edellistä sijaintia keskipisteenä.

Parametrit: säde (``R30``)

**B** - Suorakaide
^^^^^^^^^^^^^^^^^^

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

1. Ylhäällä oikealla (``J1``)
2. Ylhäällä keskellä (``J2``)
3. Ylhäällä vasemmalla (``J3``)
4. Alareunassa oikealla (``J4``)
5. Alareunassa keskellä (``J5``)
6. Alareunassa vasemmalla (``J6``)
7. Alhaalla oikealla (``J7``)
8. Alhaalla keskellä (``J8``)
9. Alhaalla vasemmalla (``J9``)
10. Puolivälissä oikealla (``J10``)
11. Puolivälissä keskellä (``J11``)
12. Puolivälissä vasemmalla (``J12``)

.. image:: ../image/alignment.png

Parametrit: asemointi (``J9``)

**S** - Tekstin absoluuttinen koko
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kooksi millimetreinä (positiivinen) tai metreinä (negatiivinen). Oletus nolla käyttää sovelluksen asetuksia. Voimassa kunnes muutetaan.

Parametrit: koko (``S2.5``)

**P** - Tekstin suhteellinen koko
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asettaa parametrin tekstin kooksi prosentteina symbolin koosta. Oletus nolla käyttää sovelluksen asetuksia. Voimassa kunnes muutetaan.

Parametrit: prosentti (``P50``)
