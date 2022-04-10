# Arcade 🕹️

## Welcome on our Arcade Project!

The goal of this project is to make a basic gaming platform in C++, that is able to switch between games and graphical libraries at runtime. In this project, each games and graphical libraries are separated in their own shared libraries.

For this project, we needed to share a common interface with another group, and make our shared libraries compatible with their platform.

Here is the email of the leader of the other group:

|mathieu.muty@epitech.eu|
|:---------------------:|

All you need to start with this project: make, g++, SFML, SDL2, SDL2_ttf, ncurses. You will need the development packages to build the graphical libraries.

For the moment, we have implemented the following games:

| Library | Games |
|:-------:|:-----:|
| [SFML](https://www.sfml-dev.org/documentation/2.5.1/)    | nibbler |
| [SDL2](https://wiki.libsdl.org/APIByCategory)     | pacman |
| [ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/) |
| [libcaca](http://transit.iut2.upmf-grenoble.fr/doc/libcaca-dev/html/caca_8h.html) |

### Documentation

Here is the [document](./doc/create_game.pdf) to create games.

Here is the [document](./doc/create_graphical_lib.pdf) to create graphical libraries.

And you can generate a doxygen documentation with the following command:

```bash
$ doxygen Doxyfile
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
 Enter                  Confirm
 R                      Restart game
Core input:
 K                      Exit game
 O                      Previous graphical library
 P                      Next graphical library
 L                      Previous game
 M                      Next game
 I                      Go back to game menu
 ```
