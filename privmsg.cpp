/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:16 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 12:57:31 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::privmsg(std::vector<std::string> receiveddata, int sockfd){

	if(receiveddata.size() == 1){
		inv_mssg(sockfd, ':' + getServerIp() + " 411 " + usernickMap[sockfd].get_nickname() + " :No recipient given (PRIVMSG)\n");
		return ;
	}
	if(receiveddata.size() == 2)
		inv_mssg(sockfd, ':' + getServerIp() + " 412 " + usernickMap[sockfd].get_nickname() + " :No text to send\n");
	else if (receiveddata[1][0] == '#')
	{
		std::string msg = "";
		msg = ':' + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@" + ClientIp(sockfd) + " PRIVMSG " + receiveddata[1] + " :" + receiveddata[2] + '\n';
		if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end())
			channelsMap[strtolower(receiveddata[1])].broadcast(msg , sockfd);
		else
			inv_mssg(sockfd, ':' + getServerIp() + " 401 " +usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such nick/channel!\n");
	}
	else if(usernickMap.find(get_sockfd(receiveddata[1])) != usernickMap.end())
	{
		std::string msg;
		msg = ':' + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@" + ClientIp(sockfd) + " PRIVMSG " + receiveddata[1] + " :" + receiveddata[2] + '\n';
		inv_mssg(get_sockfd(receiveddata[1]), msg);
	}
	else
		inv_mssg(sockfd, ':' + getServerIp() + " 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such nick/channel!\n");
	return ;
}
