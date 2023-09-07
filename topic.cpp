/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:21:27 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/06 16:34:27 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::topic(std::vector<std::string> receiveddata, int sockfd)
{
    if (receiveddata.size() >= 3){
        if(channelsMap.find(receiveddata[1]) != channelsMap.end())
        {
            if(!channelsMap[receiveddata[1]].get_is_member(sockfd))
                error(sockfd, ":irc_server 442 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :You're not on that channel\n");
            else if (!channelsMap[receiveddata[1]].get_is_operator(sockfd) && channelsMap[receiveddata[1]].get_is_topic_restricted())
                error(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :You're not channel operator\n");
            else{
                channelsMap[receiveddata[1]].set_channel_topic(receiveddata[2]);
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!irc_server TOPIC" + receiveddata[1] + ' ' + receiveddata[2] + "\n", -1);
            }
        }
        else
            error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    }
    else if (receiveddata.size() == 2)
    {
        if(channelsMap.find(receiveddata[1]) != channelsMap.end())
        {
            if(channelsMap[receiveddata[1]].get_channel_topic().empty())
                success(sockfd, ":irc_server 331 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No topic is set.\n");
            else
                success(sockfd, "channel topic: " + channelsMap[receiveddata[1]].get_channel_topic() + "\n");
        }
        else
            error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    }
    else
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " JOIN :Not enough parameters\n");
    return;
}
