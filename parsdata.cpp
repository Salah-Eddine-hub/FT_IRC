/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 14:25:42 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"
std::vector<std::string> Server::parsdata(std::string receiveddata) {
	std::vector<std::string> tokens;
	std::string word;
	
	int i = 0;
	while (receiveddata[i])
	{  
		if(receiveddata[i] == ' '){
			i++;
			continue;
		}
		if(receiveddata[i] == ':')
		{
			while (receiveddata[++i])
				word += receiveddata [i];
			tokens.push_back(word);
			break;
		}
		if(receiveddata[i] != ':')
		{
			while (receiveddata[i]){
				if (receiveddata[i] == ' ' || receiveddata[i + 1] == '\0')
				{

					if (receiveddata[i + 1] == '\0' && receiveddata[i] != ' ')
						word += receiveddata [i];
					if (!word.empty())
						tokens.push_back(word);
					word = "";
					break;
				}
				word += receiveddata[i];
				i++;
			}
		}
		i++;
	}
	return tokens;
}
