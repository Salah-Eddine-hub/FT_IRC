/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:21:27 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/26 17:49:04 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::topic(std::vector<std::string> receiveddata, int sockfd)
{
        std::string msg;

    if (receiveddata.size() >= 3){
        if(channelsMap.find(receiveddata[1]) != channelsMap.end())
        {
            if(!channelsMap[receiveddata[1]].get_is_member(sockfd))
                error(sockfd, "Error: You are not a member of the channel!\n");
            else if (channelsMap[receiveddata[1]].get_big_boss() != sockfd)
                error(sockfd, "Error: You are not an OP in this channel!\n");
            else{
                for (size_t i = 2; i < receiveddata.size(); i++)
                    msg += receiveddata[i] + ' ';
                msg[msg.size() - 1] = '\0';
                if (msg.empty() || (msg.size() == 1 && msg[0] == '\0'))
                    error(sockfd, "Error: channel's topic must not be empty!\n");
                else
                    channelsMap[receiveddata[1]].set_channel_topic(msg);
            }

        }
        else
            error(sockfd, "Error: Channel not found!\n");
    }
    else if (receiveddata.size() == 2)
    {
        if(channelsMap.find(receiveddata[1]) != channelsMap.end())
        {
            if(channelsMap[receiveddata[1]].get_channel_topic().empty())
                success(sockfd, "this channel has no topic\n");
            else
                success(sockfd, "channel topic: " + channelsMap[receiveddata[1]].get_channel_topic() + "\n");
        }
        else
            error(sockfd, "Error: Channel not found!\n");
    }
    return;
}
