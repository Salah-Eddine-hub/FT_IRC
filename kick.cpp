/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:59:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/26 14:38:45 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"


void Server::kick(std::vector<std::string> receiveddata, int sockfd)
{

    if(receiveddata.size() < 3)
        error(sockfd, "Error: wrong arguments!\n");
    else if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    {
        if (channelsMap[receiveddata[1]].get_big_boss() != sockfd)
            error(sockfd, "Error: You are not an OP in this channel!\n");
        else 
        {
            if (channelsMap[receiveddata[1]].get_is_member(get_sockfd(receiveddata[2])))
                channelsMap[receiveddata[1]].remove_the_user(get_sockfd(receiveddata[2]), receiveddata[2]);
            else
                error(sockfd, "Error: User not found!\n");
        }
    }
    else
        error(sockfd, "Error: Channel not found!\n");
    return;
}