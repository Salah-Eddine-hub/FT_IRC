# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 04:01:21 by sharrach          #+#    #+#              #
#    Updated: 2023/08/15 18:03:45 by iellyass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER =	server.hpp

SRCS =	main.cpp\
		authenticate.cpp\
		check_pass.cpp\
		server.cpp

CC =	c++
# -std=c++98
CPPFLAGS =	-Wall -Wextra -Werror 

OBJS =	$(SRCS:.cpp=.o)

RM	= rm -f

%.o: %.cpp $(HEADER)
			$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME) :	$(OBJS) $(HEADER)
			$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

all		:	$(NAME)

clean	:
		$(RM) $(OBJS)

fclean	: clean
			$(RM) $(NAME)

re		:	fclean all