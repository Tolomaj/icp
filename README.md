## ICP projekt **simulace robotů**

## Kompilace

Program se kompiluje pomocí příkazu

    make

Ovšem při prvním stažením nebo velkých změnách (hlavně v signálech) je soubor make potřeba regenerovat pomocí příkazu

    qmake -makefile

také při přidávání h souborů musí být přidány do souboru main.pro a znovu spouštěný tento příkaz


## GUI a ovládací prvky programu

V gui upravujeme scénu myší. ve spodní části si nastajeme co kliknutí myši udělá (vkládání objektů nebo jejich odebírání).
na pravé části okna je seznam objektů které se ve scéně objevují. odsud můžeme oběkty odstraňovat a ovladatelné boty ovládat.

//?***todo add image***?//


## Návrh projektu

Projekt obsahuje 2 části GUI objekt a SIMULACE objekt. \
Komunikaci mezi objěkty zařizuje objekt **mediator** který je singletronem obsahující metody k odebírání notifikací a ntifikování odběratelů. 
Je tedy možné si gui s mediatorem přidat do vlastního projektu a používat gui nezávysle na simulaci. A to platí i pro simulaci.


## Načítání/Ukládání do souboru
Načítání i ukládání lze zvolit v GUI to ovšem zašle pouze signál objektu dat simulace který soubor načte popřípadě uloží.
Data jsou ukládána ve formátu:

    BOT {X} {Y} {R} 
    BOX {X} {Y}
    AI {X} {Y} {R}
    BOX {X} {Y}

Kde X a Y jsou souřadnice a R je rotace. 
//?** TODO not done yet ?**//

## Komunikace mediatorem



## Popis souborů

|      soubor      |           popis obsahu souboru                                                                |
|------------------|-----------------------------------------------------------------------------------------------|
|simu_info.hpp     | nemnné nastavení simulace jako jsou velikost arény nebo velikosti objektů                     |
|mediator.hpp      | objekt který je komunikačním rozhraním mezi QUI a SIMULACÍ *(více v sekci Návrh Projektu)*    |
|Testing_object.h  | objekt naslouchající a vypisující konverzaci mezi gui a simulací                              |
|simulation.hpp    | object provádějící simulaci                                                                   |
|sim_data.hpp      | drží informace o všech simulovanýcho objektech, také stará se o načítání a ukládání do souboru|
|focus_colector.hpp| obsahuje singletron přez který se notifikuje který objekt byl vybrán pro gui                  |
|libs.hpp          | obsahuje všechny použité QT knihovny                                                          |
//?***todo add other files***?//
