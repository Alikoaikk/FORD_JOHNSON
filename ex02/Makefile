# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/08 01:22:36 by akoaik            #+#    #+#              #
#    Updated: 2026/03/16 01:05:46 by akoaik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

CXX		= c++
CXXFLAGS	= -g -Wall -Wextra -Werror -std=c++98

SRCS		= 	binarySearch.cpp Jacobsthal.cpp mergeSort.cpp Pmerge.cpp\
				insertSort.cpp main.cpp parsing.cpp PmergeDeque.cpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
