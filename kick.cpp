/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:59:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 11:16:19 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::kick(std::vector<std::string> receiveddata, int sockfd)
{
    if(receiveddata.size() < 3){
        inv_mssg(sockfd, ':' + localhostcheck() + " 461 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Not enough parameters\n");
        return ;
    }
    std::string tmpreceiveddata1 = receiveddata[1];
    receiveddata[1] = strtolower(receiveddata[1]);
    if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    {
        int socket = get_sockfd(receiveddata[2]);
        if (!channelsMap[receiveddata[1]].get_is_operator(sockfd) || !channelsMap[receiveddata[1]].get_is_operator(sockfd))
            inv_mssg(sockfd, ':' + localhostcheck() + " 482 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :You're not channel operator\n");
        else 
        {
            if (channelsMap[receiveddata[1]].get_is_operator(socket))
                channelsMap[receiveddata[1]].remove_the_operator(socket);
            if (channelsMap[receiveddata[1]].get_is_member(socket)) {
                if (receiveddata.size() > 3)
                    channelsMap[receiveddata[1]].remove_the_user(socket, tmpreceiveddata1, usernickMap[socket].get_nickname(), usernickMap[sockfd].get_nickname(), receiveddata[3], usernickMap[socket].get_username(), ClientIp(sockfd));
                else
                    channelsMap[receiveddata[1]].remove_the_user(socket, tmpreceiveddata1, usernickMap[socket].get_nickname(), usernickMap[sockfd].get_nickname(), "", usernickMap[socket].get_username(), ClientIp(sockfd));
                if(channelsMap[receiveddata[1]].get_current_users() == 0)
                    channelsMap.erase(receiveddata[1]);
            }
            else if(usernickMap.find(socket) != usernickMap.end())
                inv_mssg(sockfd, ':' + localhostcheck() + " 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + ' ' + tmpreceiveddata1 + " :They aren't on that channel\n");
            else
                inv_mssg(sockfd, ':' + localhostcheck() + " 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :No such nick/channel\n");
        }
    }
    else
        inv_mssg(sockfd, ':' + localhostcheck() + " 403 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata1 + " :No such channel\n");
    return;
}