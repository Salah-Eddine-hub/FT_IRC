/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:46:03 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 12:57:31 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::part(std::vector<std::string> receiveddata, int sockfd)
{
    std::map<std::string, std::string> channelAndkey;

    if(receiveddata.size() < 2) {
        inv_mssg(sockfd, ':' + getServerIp() + " 461 " + usernickMap[sockfd].get_nickname() + " PART :Not enough parameters\n");
        return ;
    }
    if (receiveddata.size() >= 2)
        channelAndkey = get_channel_and_key(receiveddata);
    for (std::map<std::string, std::string>::iterator it = channelAndkey.begin(); it != channelAndkey.end(); it++)
    {
        receiveddata[1] = it->first;
        if(channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end()) {
            channelsMap[strtolower(receiveddata[1])].leave_the_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1], usernickMap[sockfd].get_username(), getServerIp());
            if (channelsMap[strtolower(receiveddata[1])].get_is_operator(sockfd))
                channelsMap[strtolower(receiveddata[1])].remove_the_operator(sockfd);
            if (channelsMap[strtolower(receiveddata[1])].get_current_users() == 0)
                channelsMap.erase(strtolower(receiveddata[1]));
        }
        else
            inv_mssg(sockfd, ':' + getServerIp() + " 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    }
    return;
}
