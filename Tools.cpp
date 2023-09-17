/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:00:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 14:02:15 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Tools.hpp"

std::string strtolower(std::string str) {
	for (size_t i = 0; i < str.size(); ++i)
		str[i] = tolower(str[i]);
	return str;
}

std::string int_to_string(int nb) {
	std::stringstream ss;
	std::string str;

	ss << nb;
	ss >> str;
	return str;
}

int is_num(std::string arg)
{
	int i = 0;
	while (arg[i])
	{
		if (!isdigit(arg[i]))
			return i;
		i++;
	}
	return i;
}

void inv_mssg(int sockfd, const std::string& message) {
	send(sockfd, message.c_str(), message.size(), 0);
}
