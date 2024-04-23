## Kompilace

Program se kompiluje pomocí příkazu

    make

Ovšem při prvním stažením nebo velkých změnách (hlavně v signálech) je soubor make potřeba regenerovat pomocí příkazu

    qmake -makefile

také při přidávání h souborů musí být přidány do souboru main.pro a znovu spouštěný tento příkaz