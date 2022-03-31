NAME=ft_containers

CXX=c++
CPPFLAGS=-Icontainers -Iutils -Itest
CXXFLAGS=-std=c++98 -Wall -Werror -Wextra -g
# TODO: remove -g
# CXXFLAGS+=-fsanitize=address

SHELL=/usr/bin/env zsh

CONTAINERS=$(addprefix containers/, \
					 map.hpp \
					 stack.hpp \
					 vector.hpp \
					 )


UTILS=$(addprefix utils/, \
			enable_if.hpp \
			equal.hpp \
			iterator.hpp \
			make_pair.hpp \
			pair.hpp \
			vectorIterator.hpp \
			)


TESTS=$(addprefix tests/, \
			enable_if_test.cpp \
			equal_test.cpp \
			iterator_test.cpp \
			main.cpp \
			make_pair_test.cpp \
			map_test.cpp \
			pair_test.cpp \
			stack_test.cpp \
			vector_test.cpp \
			)

all: $(NAME) std_containers

std_containers: $(TESTS) tests/tests.hpp
	$(CXX) -DNS=std $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

$(NAME): $(CONTAINERS) $(UTILS) $(TESTS) tests/tests.hpp
	$(CXX) -DNS=ft $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

test: all
	if [ type valgrind &> /dev/null ]; then \
		diff --color=always <(valgrind -q --leak-check=full ./$(NAME) 2>&1) <(./std_containers); \
	else \
		diff --color=always <(./$(NAME) 2>&1) <(./std_containers); \
	fi


fclean:
	$(RM) $(NAME) std_containers

re: fclean all
