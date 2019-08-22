Ohjelman käyttö
===============

Ohjelmaa voidaan käyttää suoraan yksittäisten symbolitiedostojen editointiin tai sitä voidaan kutsua muista ohjelmista komentoriviparametreilla ohjattuna.

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

Symbolitiedoston nimi. Symbolitiedosto on tekstitiedosto, joka sisältää yksittäisen symbolin määrittelyn. Katso :ref:`symbol-format-label`.

Käyttöliittymä
--------------

Käyttöliitymä on perinteinen työpöytäkäyttöliittymä. Kaikki työkalut ovat käytettävissä valikon kautta ja tärkeimmät myös työkalupalkin painikkeina.

Valikko
^^^^^^^

Katso :doc:`menu`.

Työkalupalkki
^^^^^^^^^^^^^

Työkalupalkin ylimmällä rivillä ovat painikkeet valikon toiminnoille. Toisella rivillä on ohjelman piirron ja käyttöliittymän asetuksia. Kolmannella rivillä on symbolin mukana tallentuvia asetuksia.

Katso :doc:`tools`.

Editori
^^^^^^^

Editointi tapahtuu valitsemalla ensin valikosta tai työkalupalkista piirtotyökalu. Hiiren painikkeen painaminen aloittaa uuden elementin lisäämisen ja painikkeen vapauttaminen tallentaa sen. Luotuja elementtejä ei voi muuttaa, vaan ne on ensin poistettava ja piirrettävä sitten uudet.

Tilarivi
^^^^^^^^

Alareunan tilarivi näyttää vasemmalla hiiren koordinaatit ja oikealla symbolin tekstimuotoisen esityksen. Muoto on sama, jossa symboli tallentuu tekstitiedostoon, mutta lisäksi aktiivisen kohteen määritys on korostettu.

Asetukset
---------

Ohjelman asetukset tallentuvat seuraaviin paikkoihin käyttöjärjestelmästä riippuen:

| Linux: ``/home/<username>/.config/Syrja/SymEdit.ini``
| Windows: ``C:\Users\<username>\AppData\Roaming\Syrja\SymEdit.ini``

Asetustiedosto käyttää normaalia INI-tiedoston muotoa.
