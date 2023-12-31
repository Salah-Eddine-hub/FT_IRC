/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 14:49:31 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"
#include <ctype.h>

void Server::user_registered(int sockfd)
{

	if (usernickMap[sockfd].get_is_reg() == 0){
		inv_mssg(sockfd, ':' + getServerIp() + " 001 " + usernickMap[sockfd].get_nickname() + " :Welcome to the IRC Network " + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@" + ClientIp(sockfd) + "\n");
	}
	return ;
}

void Server::exec_cmds(std::vector<std::string> receiveddata, int sockfd){
	
	if (usernickMap[sockfd].get_nickname().empty() || usernickMap[sockfd].get_realname().empty())
	{
		if(strtolower(receiveddata[0]) == "user")
			user(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "nick")
			nick(receiveddata, sockfd);
		else {
			if (usernickMap[sockfd].get_nickname().empty())
				inv_mssg(sockfd, ':' + getServerIp() + " 451 * " + receiveddata[0] + " :You must finish connecting with another nickname first\n");
			else
				inv_mssg(sockfd, ':' + getServerIp() + " 451 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :You must finish connecting with another nickname first\n");
			return ;
		}
	}
	if (!usernickMap[sockfd].get_nickname().empty() && !usernickMap[sockfd].get_realname().empty() && usernickMap[sockfd].get_is_reg() == 0) {
		user_registered(sockfd);
		usernickMap[sockfd].set_is_reg(1);
	}
	else if (!usernickMap[sockfd].get_nickname().empty() && !usernickMap[sockfd].get_realname().empty())
	{
		if(strtolower(receiveddata[0]) == "join")
			join(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "nick")
			nick(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "user")
			user(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "list")
			list(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "privmsg")
			privmsg(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "kick")
			kick(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "invite")
			invite(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "topic")
			topic(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "mode")
			mode(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "part")
			part(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "quit")
			quit(sockfd);
		else if(strtolower(receiveddata[0]) == "bot")
			DisplayTime(receiveddata, sockfd);
		else if(strtolower(receiveddata[0]) == "pass")
			inv_mssg(sockfd, ':' + getServerIp() + " 642 " + usernickMap[sockfd].get_nickname() + " :You may not reregister\n");
		else
			inv_mssg(sockfd, ':' + getServerIp() + " 421 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Unknown command\n");
	}
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd) {

	if(check_pass(receiveddata, sockfd))
		exec_cmds(receiveddata, sockfd);    
	return ;
}
