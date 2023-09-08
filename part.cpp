/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:46:03 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/08 11:57:20 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::part(std::vector<std::string> receiveddata, int sockfd)
{
    if(receiveddata.size() < 2) {
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " PART :Not enough parameters\n");
        return ;
    }
    if(channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end()) {
        channelsMap[strtolower(receiveddata[1])].leave_the_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
        if (channelsMap[strtolower(receiveddata[1])].get_is_operator(sockfd))
            channelsMap[strtolower(receiveddata[1])].remove_the_operator(sockfd);
        if (channelsMap[strtolower(receiveddata[1])].get_current_users() == 0)
            channelsMap.erase(strtolower(receiveddata[1]));
    }
    else
        error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    return;
}
