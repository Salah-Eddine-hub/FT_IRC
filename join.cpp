/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:19:10 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/14 15:44:42 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::is_valide_name(std::string channel_name){

    for (size_t i = 1; i < channel_name.size() - 1; i++){
        if(channel_name[0] != '#' || (!isalnum(channel_name[i]) && channel_name[i] != '_'))
            return 0;
    }
    return 1;
}

void Server::join(std::vector<std::string> receiveddata, int sockfd) {
    std::map<std::string, std::string> channelAndkey;
    if (receiveddata.size() < 2){
        inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " JOIN :Not enough parameters\n");
        return ;
    }
    if (receiveddata.size() >= 2)
        channelAndkey = get_channel_and_key(receiveddata);
    
    for (std::map<std::string, std::string>::iterator it = channelAndkey.begin(); it != channelAndkey.end(); it++)
    {
        receiveddata[1] = it->first;
        if (receiveddata[1].size() < 2 || !is_valide_name(receiveddata[1]))
            inv_mssg(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");\
        else if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end()) 
        {
            std::string tmpreceiveddata1 = receiveddata[1];
            receiveddata[1] = strtolower(receiveddata[1]);
            if (!channelsMap[receiveddata[1]].get_is_member(sockfd) && channelsMap[receiveddata[1]].get_is_invite_only() && !usernickMap[sockfd].get_is_invited(receiveddata[1]))
                inv_mssg(sockfd, ":irc_server 473 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :Cannot join channel (+i)\n");
            else if (!channelsMap[receiveddata[1]].get_is_pwd_needed().empty()) 
            {
                if (receiveddata.size() < 3){
                    inv_mssg(sockfd, ":irc_server 475 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :Cannot join channel (+k)\n");
                    continue;
                }
                std::string pwd = channelAndkey[it->first];
                if (channelsMap[receiveddata[1]].get_is_pwd_needed() != pwd)
                    inv_mssg(sockfd, ":irc_server 475 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :Cannot join channel (+k)\n");
                else if (channelsMap[receiveddata[1]].get_is_pwd_needed() == pwd)
                    channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), tmpreceiveddata1 , usernickMap);
            }
            else
                channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), tmpreceiveddata1 , usernickMap);
        }
        else {
            channelsMap[strtolower(receiveddata[1])] = Channel(receiveddata[1]);
            channelsMap[strtolower(receiveddata[1])].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1], usernickMap);
            channelsMap[strtolower(receiveddata[1])].set_is_operator(sockfd);
            channelsMap[strtolower(receiveddata[1])].set_is_pwd_needed(channelAndkey[it->first]);
        }
    }
    return ;
}
