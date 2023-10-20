/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:11:06 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 14:25:37 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"

int Server::is_valide_nickname(std::string &nickname, int sockfd)
{
	int i = 0;
	std::string holder = "";

	if (!isalpha(nickname[0]) && nickname[0] != '_') {
		if(usernickMap[sockfd].get_nickname().empty())
			inv_mssg(sockfd, ':' + getServerIp() + " 432 "+ nickname +" :Erroneous Nickname\n");
		else
			inv_mssg(sockfd, ':' + getServerIp() + " 432 " + usernickMap[sockfd].get_nickname() + ' ' + nickname + " :Erroneous Nickname\n");
		return 0;
	}
	while (isalpha(nickname[i]) || nickname[i] == '_' || isdigit(nickname[i])) {
		holder += nickname[i];
		i++;
	}
	nickname = holder;
	return 1;
}

void Server::nick(std::vector<std::string> receiveddata, int sockfd) {

	std::map<int, Client>::iterator it;
	if (receiveddata.size() < 2){
		if (!usernickMap[sockfd].get_nickname().empty())
			inv_mssg(sockfd, ':' + getServerIp() + " 431 " + usernickMap[sockfd].get_nickname() + " :No nickname given\n");
		else
			inv_mssg(sockfd, ':' + getServerIp() + " 431  :No nickname given\n");
		return ;
	}
	else{
		for (it = usernickMap.begin(); it != usernickMap.end(); it++){
			if(strtolower(it->second.get_nickname()) == strtolower(receiveddata[1]) && sockfd != get_sockfd(it->second.get_nickname())) {
				if(usernickMap[sockfd].get_nickname().empty()){
					inv_mssg(sockfd, ':' + getServerIp() + " 433 * " + receiveddata[1] + " :Nickname is already in use.\n");
					return ;
				}
				else if(strtolower(usernickMap[sockfd].get_nickname()) == strtolower(receiveddata[1]))
					return ;
				else
					inv_mssg(sockfd, ':' + getServerIp() + " 433 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :Nickname is already in use.\n");
				return ;
			}
		}
		if (usernickMap[sockfd].get_is_reg() && is_valide_nickname(receiveddata[1], sockfd)) {
			if (usernickMap[sockfd].get_nickname() != receiveddata[1]) {
				inv_mssg(sockfd, ':' + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@" + ClientIp(sockfd) + " NICK :" + receiveddata[1] + '\n');
				usernickMap[sockfd].set_nickname(receiveddata[1]);
			}
		}
		else if (is_valide_nickname(receiveddata[1], sockfd))
			usernickMap[sockfd].set_nickname(receiveddata[1]);
	}
	return ;
}
