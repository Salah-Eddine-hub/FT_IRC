/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:46:03 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/07 19:04:53 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::part(std::vector<std::string> receiveddata, int sockfd)
{
    if(receiveddata.size() < 2) {
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " PART :Not enough parameters\n");
        return ;
    }
    receiveddata[1] = strtolower(receiveddata[1]);
    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        channelsMap[receiveddata[1]].leave_the_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
        if (channelsMap[receiveddata[1]].get_is_operator(sockfd))
            channelsMap[receiveddata[1]].remove_the_operator(sockfd);
        if (channelsMap[receiveddata[1]].get_current_users() == 0)
            channelsMap.erase(receiveddata[1]);
    }
    else
        error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    return;
}
