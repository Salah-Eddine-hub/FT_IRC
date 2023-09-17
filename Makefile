# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 04:01:21 by sharrach          #+#    #+#              #
#    Updated: 2023/09/17 14:02:03 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER =	Server.hpp Channel.hpp Tools.hpp

SRCS =	Server.cpp\
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
		quit.cpp\
		Tools.cpp

CC =	c++

CPPFLAGS =	-Wall -Wextra -Werror -std=c++98

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