# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 04:01:21 by sharrach          #+#    #+#              #
#    Updated: 2023/08/24 18:17:11 by iellyass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER =	server.hpp Channel.hpp Tools.hpp

SRCS =	server.cpp\
		Channel.cpp\
		Client.cpp\
		privmsg.cpp\
		authenticate.cpp\
		check_pass.cpp\
		parsdata.cpp\
		join.cpp\
		list.cpp\
		print_error.cpp\
		main.cpp\
		msg.cpp\
		check_reg_and_cmds.cpp\
		Tools.cpp

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