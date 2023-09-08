/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:59:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/08 12:34:06 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::kick(std::vector<std::string> receiveddata, int sockfd)
{
    if(receiveddata.size() < 3){
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Not enough parameters\n");
        return ;
    }
    std::string tmpreceiveddata1 = receiveddata[1];
    receiveddata[1] = strtolower(receiveddata[1]);
    // receiveddata[2] = strtolower(receiveddata[2]);
    if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    {
        int socket = get_sockfd(receiveddata[2]);
        if (!channelsMap[receiveddata[1]].get_is_operator(sockfd) || !channelsMap[receiveddata[1]].get_is_operator(sockfd))
            error(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :You're not channel operator\n");
        else 
        {
            if (channelsMap[receiveddata[1]].get_is_operator(socket))
                channelsMap[receiveddata[1]].remove_the_operator(socket);
            if (channelsMap[receiveddata[1]].get_is_member(socket)) {
                channelsMap[receiveddata[1]].remove_the_user(socket, usernickMap[socket].get_nickname(), usernickMap[sockfd].get_nickname());
                if(channelsMap[receiveddata[1]].get_current_users() == 0)
                    channelsMap.erase(receiveddata[1]);
            }
            else if(usernickMap.find(socket) != usernickMap.end())
                error(sockfd, ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + ' ' + tmpreceiveddata1 + " :They aren't on that channel\n");
            else
                error(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :No such nick/channel\n");
        }
    }
    else
        error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata1 + " :No such channel\n");
    return;
}