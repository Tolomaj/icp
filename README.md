## ICP projekt **simulace robotů**

## Kompilace

Program se kompiluje pomocí příkazu specifikovaných v zadání.

Ke zkompilování programu použijte:

    make 

K vytvoření dokumentace použijte:

    make doxygen

Ta se vygeneruje do složky docs/html
Ve složce docs/doxygen-awesome-css jsou styli které zvyšují přehlednost dokumentace

## Implementovaná funkcionalita

### Plně inplementované
- přidávání objektů do scény
- odebírání objektů ve scéně
- ovládání simulace
- načítání a ukládání scén
- označení robotů pro přehledné sledování
- ovládání ovladatelných robotů ze seznamu objektů
- kolize a otáčení robotů
- nastavování parametrů robotů při přidávání do scény

### Neinplementované
- editace již existujících objektů
- odstranení všech objektů ve scéně tlačítkem (lze obejít načtením prázdného souboru)



## Rozdělení projektu
Projekt jsme inplementovali společně proto je tešší rozdelit kdo co přesně dělal. Ovšem projekt je rozdělený do dvou částí a každný měl zodpovědnost za svoji.

- GUI (složka gui) byla zodpovědností xgross13
- Simulace (složka sim) byla zodpovědností xfolty21
- Mediator (složka link) byla zodpovědností xgross13


## Návrh projektu

Projekt obsahuje 2 části GUI objekt a SIMULACE objekt. \
Komunikaci mezi objěkty zařizuje objekt **mediator** který je singletronem obsahující metody k odebírání notifikací a notifikování odběratelů. 
Je tedy možné si gui s mediatorem přidat do vlastního projektu a používat gui nezávysle na simulaci. A to platí i pro simulaci.



## GUI a ovládací prvky programu

V gui upravujeme scénu myší. ve spodní části si nastajeme co kliknutí myši udělá (vkládání objektů nebo jejich odebírání).
na pravé části okna je seznam objektů které se ve scéně objevují. odsud můžeme oběkty odstraňovat a ovladatelné boty ovládat.

//?***todo add image***?//


## Načítání/Ukládání do souboru
Načítání i ukládání lze zvolit v GUI to ovšem zašle pouze signál objektu dat simulace který soubor načte popřípadě uloží.
Data jsou ukládána ve formátu:

    BOT {X} {Y} {R} 
    BOX {X} {Y}
    AI {X} {Y} {R}
    BOX {X} {Y}

Kde X a Y jsou souřadnice a R je rotace. 
//?** TODO not done yet ?**//
