NAME=ft_containers

CXX=c++
CPPFLAGS=-Icontainers -Iutils -Itests
CXXFLAGS=-std=c++98 -Wall -Werror -Wextra
# CXXFLAGS+= -g
# CXXFLAGS+=-fsanitize=address
# TODO: remove -g and -fsanitize

SHELL=/usr/bin/env zsh

CONTAINERS=$(addprefix containers/, \
					 map.hpp \
					 stack.hpp \
					 vector.hpp \
					 )


UTILS=$(addprefix utils/, \
			type_traits.hpp \
			lexicographical_compare.hpp \
			iterator.hpp \
			pair.hpp \
			vectorIterator.hpp \
			AVLTree.hpp \
			swap.hpp \
			)


TESTS=$(addprefix tests/, \
			main.cpp \
			map_test.cpp \
			stack_test.cpp \
			vector_test.cpp \
			utils_test.cpp \
			avl_test.cpp \
			subject_tests.cpp \
			)

all: $(NAME) std_containers

std_containers: $(TESTS) tests/tests.hpp
	$(CXX) -DNS=std $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

$(NAME): $(CONTAINERS) $(UTILS) $(TESTS) tests/tests.hpp
	$(CXX) -DNS=ft $(CPPFLAGS) $(CXXFLAGS) $(TESTS) -o $@

test: all
	./$(NAME) &> output_ft
	./std_containers &> output_std
	diff --color=always output_ft output_std && rm output_ft output_std && echo Same Output !
	@cat timing;sleep 1; rm timing;

fclean:
	$(RM) $(NAME) std_containers

re: fclean all
