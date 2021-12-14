Harjoitustyövaiheen 2 readme dokumentti:

Tietorakenne: 
Pidin kaupunkien tietorakenteet samana kuin ensimmäisessä vaiheessa. Ainoa muutos tapahtui kaupungin struct rakenteessa, johon lisäsin vector rakenteen kaupungista lähteville teille. Vector sisältää alkioina parin, jossa on osoitin kaupungiin, johon tie johtaa, ja Distance mitta tien pituudesta. Lisäsin kaupungin structiin colour, d, ja path_back tiedot. Näitä tarvitaan graafi algoritmeissa, joita tehtiin tässä harjoitustyössä. Colour on enum rakenne joka sisältää värit WHITE, GRAY, BLACK. D on float tyyppinen, koska se usein saa alustuksessa arvon INFINITY. Path_back on osoitin yhteen kaupunkiin.

Funktiot:
All_roads funktiossa käytin tietorakennetta set, johon ei pysty lisäämään samaa tietä uudestaan. Monessa funktiossa käytin find() komentoa kaupungin etsimiseen towns_ mapista. Tämä on tehokkuudeltaan keskimäärin vakio.
Any_route ja road_cycle_route funktioissa käytin syvyys-ensin-hakua ja least_towns_route funktiossa leveys-ensin-hakua. Näillä operaatioilla on kiinteät tehokkuudet eikä niihin oikein itse pysty vaikuttamaan. Remove_road funktiossa bool arvoista find_road muuttujaa, jonka avulla voin varmistaa, ettei turhaan käydä molempien kaupunkien teitä, jos se ei löydy ensimmäisen kaupungin teistä. Shortest_route funktiossa käytin A* algoritmiä, joka on tehokkuudeltaan hieman huonompi kuin muut funktiot, mutta se on oikeastaan ainoa järkevä tapa löytää kaupunkien välinen lyhyin reitti.
