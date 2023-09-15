/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:34:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/15 23:40:50 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::invite(std::vector<std::string> receiveddata, int sockfd)
{
    std::map<std::string, std::string> channelAndkey;

    if(receiveddata.size() < 3){
        inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " INVITE :Not enough parameters\n");
        return;
    }
    if(usernickMap.find(get_sockfd(receiveddata[1])) != usernickMap.end() )
    {
        std::string tmpreceiveddata2 = receiveddata[2];
        std::string tmpreceiveddata1 = receiveddata[1];
        receiveddata[2] = strtolower(receiveddata[2]);
        receiveddata[1] = strtolower(receiveddata[1]);
        if (channelsMap.find(receiveddata[2]) == channelsMap.end())
            inv_mssg(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata2 + " :No such channel\n");
        else if(!channelsMap[receiveddata[2]].get_is_member(sockfd)) 
            inv_mssg(sockfd, ":irc_server 442 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata2 + " :You're not on that channel\n");
        else 
        {
            if (channelsMap[receiveddata[2]].get_is_member(get_sockfd(receiveddata[1])))
                inv_mssg(sockfd, ":irc_server 443 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata1 + ' ' + channelsMap[receiveddata[2]].get_original_channel_name() + " :is already on channel\n");
            else if (!channelsMap[receiveddata[2]].get_is_operator(sockfd))
                inv_mssg(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[2]].get_original_channel_name() + " :You're not channel operator\n");
            else {
                usernickMap[get_sockfd(receiveddata[1])].set_is_invited(receiveddata[2]);
                inv_mssg(get_sockfd(receiveddata[1]), ":" + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@localhost INVITE " + receiveddata[1] + " :" + receiveddata[2] + "\n");
                inv_mssg(sockfd, ":irc_server 341 " + usernickMap[sockfd].get_nickname() + ' ' + usernickMap[get_sockfd(receiveddata[1])].get_nickname() + ' ' + receiveddata[2] + "\n");
                channelsMap[strtolower(receiveddata[2])].broadcast(":irc_server NOTICE @" + receiveddata[2] + " :" + usernickMap[sockfd].get_nickname() + " invited " + usernickMap[get_sockfd(receiveddata[1])].get_nickname() + " into channel " + receiveddata[2] + " \n", -1);
            }
        }
    }
    else
        inv_mssg(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such nick/channel\n");
    return;
}
