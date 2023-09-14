/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:21:27 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/12 13:46:49 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::topic(std::vector<std::string> receiveddata, int sockfd)
{
    if (receiveddata.size() >= 3){
        std::string tmpreceiveddata1 = receiveddata[1] ;
        receiveddata[1] = strtolower(receiveddata[1]);
        if(channelsMap.find(receiveddata[1]) != channelsMap.end())
        {
            if(!channelsMap[receiveddata[1]].get_is_member(sockfd))
                inv_mssg(sockfd, ":irc_server 442 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata1 + " :You're not on that channel\n");
            else if (!channelsMap[receiveddata[1]].get_is_operator(sockfd) && channelsMap[receiveddata[1]].get_is_topic_restricted())
                inv_mssg(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :You're not channel operator\n");
            else{
                channelsMap[receiveddata[1]].set_channel_topic(receiveddata[2]);
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost TOPIC " + channelsMap[receiveddata[1]].get_original_channel_name() + " :" + receiveddata[2] + "\n", -1);
            }
        }
        else
            inv_mssg(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + tmpreceiveddata1 + " :No such channel\n");
    }
    else if (receiveddata.size() == 2)
    {
        if(channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end())
        {
            if(channelsMap[receiveddata[1]].get_channel_topic().empty())
                inv_mssg(sockfd, ":irc_server 331 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :No topic is set.\n");
            else
                inv_mssg(sockfd, ":irc_server 332 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + ' ' + channelsMap[strtolower(receiveddata[1])].get_channel_topic() + "\n");
        }
        else
            inv_mssg(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
    }
    else
        inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " TOPIC :Not enough parameters\n");
    return;
}
