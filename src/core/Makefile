##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CXX = g++

CXXFLAGS = -W -Wall -Werror -fno-gnu-unique -std=c++20 -g -I../../include

LFLAGS = -ldl

TEST_FLAGS = $(LFLAGS) -lgtest -lgcov -lpthread --coverage -fprofile-arcs \
	-ftest-coverage

TARGET = ../../arcade

TARGET_TEST = unit_tests

SRC =	Manager.cpp \
		GameMenu.cpp \

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
	rm -f $(OBJ)
	rm -f *.gc* unit_tests

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all re tests_run coverage clean fclean
