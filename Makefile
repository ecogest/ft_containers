NAME=ft_containers

CC=c++
INCLUDE=-I.
CXXFLAGS=-std=c++98 -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	$(CC) $(INCLUDE) $(CXXFLAGS) Tests/main.cpp
