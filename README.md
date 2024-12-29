# Breakout Game

Tento projekt je jednoduchá implementace hry **Breakout** napsaná v jazyce C pomocí knihoven SDL2.

## Požadavky

Pro spuštění této hry je třeba mít nainstalované následující knihovny:

- **SDL2**: Základní knihovna pro vykreslování, ovládání a události.
- **SDL2_ttf**: Pro práci s textem a fonty.
- **SDL2_image**: Pro práci s obrázky.

### Instalace knihoven na Linux

Použij následující příkazy pro instalaci potřebných balíčků:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev build-essential
```

## Struktura projektu

Projekt má následující strukturu:

```
.
├── src/                # Zdrojové soubory hry
│   ├── main.c
│   ├── menu.c
│   ├── utils.c
│   ├── scoreboard.c
│   ├── game.c
├── include/            # Hlavičkové soubory
│   ├── menu.h
│   ├── utils.h
│   ├── scoreboard.h
│   ├── game.h
├── assets/             # Soubory fontů a obrázků
│   ├── Audiowide-Regular.ttf
│   ├── paddle.svg
│   ├── ball.svg
│   ├── brick(1-6).png
├── Makefile            # Makefile pro kompilaci
├── README.md           # Dokumentace projektu
├── score.txt           # Soubor se zaznamem score
```

---

## Překlad

Pro překlad použij Makefile:

```bash
make
```

Pokud budeš chtít odstranit binární soubory a objektové soubory, použij:

```bash
make clean
```

---

## Spuštění

Po úspěšném překladu spusť binární soubor `breakout`:

```bash
./breakout
```

---

## Jak to funguje?

1. **Menu**:
    - Při spuštění se zobrazí hlavní menu s názvem hry, tlačítkem "START" a tabulkou nejlepších skóre.
    - Použij **myš** k výběru nebo **klávesu ESC** pro ukončení.

2. **Hra**:
    - Ovládáš pálku pomocí **šipek doleva a doprava**.
    - Tlačítko **SPACE** odpálí míček (i když po ztrátě života).
    - Cílem zničit všechny cihly.

3. **Tabulka skóre**:
    - Po skončení hry se uloží dosažené skóre do souboru `score.txt` a zobrazí se v tabulce v menu.

---

## Přizpůsobení

- **Fonty a obrázky**: Můžeš upravit soubory v adresáři `assets/`, například změnit font nebo nahradit obrázky míčku, pálky a cihel.
- **Logika hry**: Úpravy velikosti pálky, rychlosti míčku, počtu cihel, atd. můžeš provést v souborech `game.c` a `game.h`.

---

## Autor

- **MAT0586**
- e-mail: marek.matyskiewicz.st@vsb.cz
