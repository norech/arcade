##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

API_DIR = $(PWD)/include/spc

all:
	make -C src/common/
	make -C src/core/
	make -C src/ncurses/
	make -C src/sdl/
	make -C src/pacman/
	make -C src/sfml/
	make -C src/nibbler

core:
	make -C src/core/

games:
	make -C src/common/
	make -C src/pacman/
	make -C src/nibbler/

graphicals:
	make -C src/common/
	make -C src/ncurses/
	make -C src/sdl/
	make -C src/sfml/

clean:
	make -C src/common/ clean
	make -C src/core/ clean
	make -C src/ncurses/ clean
	make -C src/sdl/ clean
	make -C src/pacman/ clean
	make -C src/sfml/ clean
	make -C src/nibbler/ clean

fclean:
	make -C src/common/ fclean
	make -C src/core/ fclean
	make -C src/ncurses/ fclean
	make -C src/sdl/ fclean
	make -C src/pacman/ fclean
	make -C src/sfml/ fclean
	make -C src/nibbler/ fclean

api:
	git clone git@github.com:norech/special-arcade.git /tmp/arcade
	cd /tmp/arcade && git checkout impl1
	rm -rf $(API_DIR)
	mkdir -p $(API_DIR)
	cp -r /tmp/arcade/interface/* $(API_DIR)
	rm -rf /tmp/arcade

re: fclean all

.PHONY: all re tests_run coverage clean fclean
