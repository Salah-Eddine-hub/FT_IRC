# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 04:01:21 by sharrach          #+#    #+#              #
#    Updated: 2023/09/14 18:04:54 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER =	server.hpp Channel.hpp Tools.hpp

SRCS =	server.cpp\
		Channel.cpp\
		Client.cpp\
		privmsg.cpp\
		check_pass.cpp\
		parsdata.cpp\
		join.cpp\
		list.cpp\
		main.cpp\
		invite.cpp\
		mode.cpp\
		kick.cpp\
		topic.cpp\
		part.cpp\
		nick.cpp\
		user.cpp\
		check_reg_and_cmds.cpp\
		bot.cpp\
		Tools.cpp

CC =	c++

CPPFLAGS =	-Wall -Wextra -Werror -std=c++98 -fsanitize=address

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