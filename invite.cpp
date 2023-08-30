/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:34:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 18:21:11 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::invite(std::vector<std::string> receiveddata, int sockfd)
{

    if(receiveddata.size() < 3)
        error(sockfd, "Error: wrong arguments!\n");
    else if(channelsMap.find(receiveddata[2]) != channelsMap.end() )
    {
        if(!channelsMap[receiveddata[2]].get_is_member(sockfd)) 
            error(sockfd, "Error: You are not a member of the channel!\n");
        else if (!channelsMap[receiveddata[2]].get_is_operator(sockfd))
            error(sockfd, "Error: You are not an OP in this channel!\n");
        else 
        {
            if (usernickMap.find(get_sockfd(receiveddata[1])) == usernickMap.end())
                error(sockfd, "Error: User not found!\n");
            else if (channelsMap[receiveddata[2]].get_is_member(get_sockfd(receiveddata[1])))
                error(sockfd, "Error: " + receiveddata[1] + " already a member of this channel!\n");
            else {
                usernickMap[get_sockfd(receiveddata[1])].set_is_invited(receiveddata[2]);
                success(get_sockfd(receiveddata[1]), usernickMap[sockfd].get_nickname() + " invited you to join " + receiveddata[2] + "!\n");
            }
        }
    }
    else
        error(sockfd, "Error: Channel not found!\n");
    return;
}