# Arcade 🕹️

## Welcome on our Arcade Project!

The goal of this project is to make an app in C++<br>
to load an unload in runtime games and graphicals library

for this project whe need to share our interfaces with an other group

here the email of the leader of the other group

|mathieu.muty@epitech.eu|
|:---------------------:|

all You need to start is make g++ sfml sdl ncurses ...
and the development kit of the graphic library

for the moment whe have implemented 

| Library | Games |
|:-------:|:-----:|
| [SFML](https://www.sfml-dev.org/documentation/2.5.1/)    | nibbler |
| [SDL2](https://wiki.libsdl.org/APIByCategory)     | pacman |
| [ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/) |
| [libcaca](http://transit.iut2.upmf-grenoble.fr/doc/libcaca-dev/html/caca_8h.html) |

### Documentation

here is the docs [docs](https://github.com/EpitechPromo2025/B-OOP-400-RUN-4-1-arcade-ludovic.peltier/blob/cmake/doc/create_game.pdf) to create games

here is the [docs](https://github.com/EpitechPromo2025/B-OOP-400-RUN-4-1-arcade-ludovic.peltier/blob/cmake/doc/create_graphical_lib.pdf) to create graphics api

and you can generate doxygen documentation

```bash
   doxygen .
```
### Compile

```bash
   $ make
```

### Usage

```
Usage: ./arcade [graphical_library.so]

Common game input:
 ZQSD / Arrows          Move
 I / Enter              Confirm
 R                      Restart game
Core input:
 K                      Exit game
 O                      Previous graphical library
 P                      Next graphical library
 ```
 






