##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

API_DIR = $(PWD)/include/spc

all:
	make -C src/core/
	make -C src/ncurses/
	make -C src/sdl/

core:
	make -C src/core/

games:
	make -C src/games/

graphicals:
	make -C src/ncurses/
	make -C src/sdl/

clean:
	make -C src/core/ clean
	#make -C src/ncurses/ clean
	make -C src/sdl/ clean

fclean:
	make -C src/core/ fclean
	make -C src/ncurses/ fclean
	make -C src/sdl/ fclean

api:
	git clone git@github.com:norech/special-arcade.git /tmp/arcade
	rm -rf $(API_DIR)
	mkdir -p $(API_DIR)
	cp -r /tmp/arcade/interface/* $(API_DIR)
	rm -rf /tmp/arcade

re: fclean all

.PHONY: all re tests_run coverage clean fclean
