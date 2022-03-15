##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CXX = g++

CFLAGS = -shared -fPIC -fno-gnu-unique -W -Wall -Werror -std=c++20 -g \
	-I../include

LFLAGS = -lncurses

TEST_FLAGS = $(LFLAGS) -lgtest -lgcov -lpthread --coverage -fprofile-arcs \
	-ftest-coverage

TARGET = ../../lib/arcade_ncurses.so

TARGET_TEST = unit_tests

SRC =	\

TESTS =	\

OBJ_TESTS = $(SRC:.cpp=.o) $(TESTS:.cpp=.o)

OBJ = $(SRC:.cpp=.o) main.o

all: $(TARGET)

build_all: ${OBJ}
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ) $(LFLAGS)

tests_run: clean_tests ${OBJ_TESTS}
	$(CXX) $(CFLAGS) $(TEST_FLAGS) -o $(TARGET_TEST) $(OBJ_TESTS) $(LFLAGS)
	./$(TARGET_TEST) --verbose

coverage:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

clean_tests:
	rm -rf $(TARGET_TEST)

$(TARGET): build_all

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f $(OBJ)
	rm -f *.gc* unit_tests

re: fclean all

.PHONY: all re tests_run coverage clean fclean
