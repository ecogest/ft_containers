NAME=ft_containers

CXX=c++
CPPFLAGS=-Icontainers -Iutils -Itest
CXXFLAGS=-std=c++98 -Wall -Werror -Wextra

SHELL=/usr/bin/env zsh

CONTAINERS=$(addprefix containers/, \
					 map.hpp \
					 stack.hpp \
					 vector.hpp \
					 )


UTILS=$(addprefix utils/, \
			enable_if.hpp \
			equal.hpp \
			iterator_traits.hpp \
			make_pair.hpp \
			pair.hpp \
			reverse_iterator.hpp \
			)


TESTS=$(addprefix tests/, \
			enable_if_test.cpp \
			equal_test.cpp \
			iterator_traits_test.cpp \
			main.cpp \
			make_pair_test.cpp \
			map_test.cpp \
			pair_test.cpp \
			reverse_iterator_test.cpp \
			stack_test.cpp \
			vector_test.cpp \
			)

all: $(NAME) std_containers

std_containers: $(TESTS) tests/tests.hpp
	$(CXX) -DNS=std $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

$(NAME): $(CONTAINERS) $(UTILS) $(TESTS) tests/tests.hpp
	$(CXX) -DNS=ft $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

test: all
	diff --color=always <(./$(NAME)) <(./std_containers)

fclean:
	$(RM) $(NAME) std_containers

re: fclean all