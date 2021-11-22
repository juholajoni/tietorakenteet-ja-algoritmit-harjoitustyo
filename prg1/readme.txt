Projektin readme dokumentti

Tietorakenne:
Valitsin unordered_mapin tietorakenteeksi, jossa pidän kaikki kaupungit, koska siinä kaupunkien lisääminen/poistaminen on tyypillisesti nopeampaa kuin mapissa. Avaimeksi valitsin TownID tyypin, koska se annetaan useissa funktioissa parametrina. Hyötykuormana on struct rakenne, jossa on kaupungin tiedot. Siellä on uudestaan TownID, koska remove_town funktiossa tarvitaan kaupungin isännän id ja isäntänä on vain osoitin sen structiin, joten structissa täytyy myös olla TownID. Kaupungin vassalit talletetaan vektoriin, jossa on vassalien TownID, koska muuta ei tarvitse vassaleista tietää. Isäntä toimii osoitin, koska isäntiä voi olla vain yksi per kaupunki. 

Huomioita funktioista:
Käytin find() operaatiota, kun tarkistin löytyykö id:tä vastaavaa kaupunkia unordered_mapista, koska se operaatio on keskimäärin vakio. Eli tehokkaampi kuin esimerkiksi count() operaatio.
Get funktioiden tehokkuuksiksi sain vakiot tekemällä osoittimen find() operaatiolla, josta oli sitten helppo saada tarvittavat tiedot
Järjestysfunktioissa tein kaksi eri vektoria eli niin sanotun info vektorin, joka sisältää tietoa sorttaamista varten ja palautusvektorin joka sisältää vain TownId arvoja. Tällä tavalla tehokkuus pysyi lineaarisena.
Remove funktiossa käytin find algoritmia, jotta ei tarvitse vassaleita käydä lävitse for loopissa.
Longest_vassal_path ja total_net_tax funktioissa tein omat apufunktiot, joissa rekursion avulla pääsin tietorakenteessa syvemmälle. 

