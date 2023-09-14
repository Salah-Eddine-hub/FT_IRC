/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:01:31 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/14 16:01:47 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"
#include <chrono>

void Server::DisplayTime(const std::string username, int sockfd) {
	
	if (username.empty())
	{
		inv_mssg(sockfd, "wrong args.\n");
		return ;
	}
	if (usernickMap.find(get_sockfd(strtolower(username))) != usernickMap.end()) {
		std::time_t loginTime = usernickMap[get_sockfd(strtolower(username))].get_loginTimesg();
		std::cout << "loginTime time " <<  loginTime  << std::endl;
		std::time_t currentTime = std::time(NULL);
		std::time_t duration = currentTime - loginTime;
		int minutes = static_cast<int>(duration / 60);
		std::cout << minutes << std::endl;
		std::stringstream ss;
		std::string str_min;
		ss << minutes;
		ss >> str_min;
		inv_mssg(sockfd, username + " has been logged in for " +  str_min + " minutes.\n");
	}
	else {
		inv_mssg(sockfd, "User " + username + " not found.\n");
	}
}