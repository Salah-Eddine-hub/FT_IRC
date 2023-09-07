/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:34:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/06 16:17:28 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::invite(std::vector<std::string> receiveddata, int sockfd)
{

    if(receiveddata.size() < 3)
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " INVITE :Not enough parameters\n");
    
    else if(usernickMap.find(get_sockfd(receiveddata[1])) != usernickMap.end() )
    {
        if (channelsMap.find(receiveddata[2]) == channelsMap.end())
            error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :No such channel\n");
        else if(!channelsMap[receiveddata[2]].get_is_member(sockfd)) 
            error(sockfd, ":irc_server 442 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :You're not on that channel\n");
        else 
        {
            if (channelsMap[receiveddata[2]].get_is_member(get_sockfd(receiveddata[1])))
                error(sockfd, ":irc_server 443 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + receiveddata[2] + " :is already on channel\n");
            else if (!channelsMap[receiveddata[2]].get_is_operator(sockfd))
                error(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :You're not channel operator\n");
            else {
                usernickMap[get_sockfd(receiveddata[1])].set_is_invited(receiveddata[2]);
                success(get_sockfd(receiveddata[1]), ":ha1!irc_server INVITE " + receiveddata[1] + " :" + receiveddata[2] + "\n");
                success(sockfd, ":irc_server 341 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + receiveddata[2] + "\n");
                success(sockfd, ":irc_server NOTICE @" + receiveddata[2] + " :" + usernickMap[sockfd].get_nickname() + " invited " + receiveddata[1] + " into channel " + receiveddata[2] + " \n");
            }
        }
    }
    else
        error(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[2] + " :No such nick/channel\n");
    return;
}
