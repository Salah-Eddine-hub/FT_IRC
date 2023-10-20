/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:01:31 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/17 14:51:02 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

void Server::DisplayTime(std::vector<std::string> receiveddata, int sockfd) {
	
	if (receiveddata.size() < 2)
	{
		inv_mssg(sockfd, "wrong args.\n");
		return ;
	}
	if (usernickMap.find(get_sockfd(strtolower(receiveddata[1]))) != usernickMap.end()) {
		std::time_t loginTime = usernickMap[get_sockfd(strtolower(receiveddata[1]))].get_loginTimesg();
		std::time_t currentTime = std::time(NULL);
		std::time_t duration = currentTime - loginTime;
		int minutes = static_cast<int>(duration / 60);
		std::stringstream ss;
		std::string str_min;
		ss << minutes;
		ss >> str_min;
		inv_mssg(sockfd, receiveddata[1] + " has been logged in for " +  str_min + " minutes.\n");
	}
	else {
		inv_mssg(sockfd, "User " + receiveddata[1] + " not found.\n");
	}
}