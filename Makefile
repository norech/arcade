##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

API_DIR = $(PWD)/include/spc

DOCS = 	doc/create_game.md \
		doc/create_graphical_lib.md \

PDF = $(DOCS:.md=.pdf)

all:
	mkdir -p lib
	make -C src/common/
	make -C src/core/
	make -C src/ncurses/
	make -C src/sdl/
	make -C src/pacman/
	make -C src/sfml/
	make -C src/nibbler
	make -C src/libcaca/

core:
	mkdir -p lib
	make -C src/core/

games:
	mkdir -p lib
	make -C src/common/
	make -C src/pacman/
	make -C src/nibbler/

graphicals:
	mkdir -p lib
	make -C src/common/
	make -C src/ncurses/
	make -C src/sdl/
	make -C src/sfml/
	make -C src/libcaca/

clean:
	make -C src/common/ clean
	make -C src/core/ clean
	make -C src/ncurses/ clean
	make -C src/sdl/ clean
	make -C src/pacman/ clean
	make -C src/sfml/ clean
	make -C src/nibbler/ clean
	make -C src/libcaca/ clean

fclean:
	make -C src/common/ fclean
	make -C src/core/ fclean
	make -C src/ncurses/ fclean
	make -C src/sdl/ fclean
	make -C src/pacman/ fclean
	make -C src/sfml/ fclean
	make -C src/nibbler/ fclean
	make -C src/libcaca/ fclean
api:
	git clone git@github.com:norech/special-arcade.git /tmp/arcade
	cd /tmp/arcade && git checkout impl1
	rm -rf $(API_DIR)
	mkdir -p $(API_DIR)
	cp -r /tmp/arcade/interface/* $(API_DIR)
	rm -rf /tmp/arcade

re: fclean all

%.pdf: %.md
	pandoc -s -o $@ $<

doc: $(PDF)
	mkdir -p doc/doxygen
	doxygen Doxyfile

.PHONY: all re tests_run coverage clean fclean doc
