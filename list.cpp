/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:33:40 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 12:57:31 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

void Server::list(std::vector<std::string> receiveddata, int sockfd) {

    std::map<std::string, std::string> channelAndkey;
    std::string msg;
    std::map<std::string, Channel>::const_iterator it;

    msg = ':' + getServerIp() + " 321 " + usernickMap[sockfd].get_nickname() + " Channel :Users Name\n";
    inv_mssg(sockfd, msg);
    // if (receiveddata.size() >= 2)
    //     channelAndkey = get_channel_and_key(receiveddata);
    if (receiveddata.size() > 1) {
        channelAndkey = get_channel_and_key(receiveddata);
        for (std::map<std::string, std::string>::iterator it = channelAndkey.begin(); it != channelAndkey.end(); it++)
        {
            receiveddata[1] = it->first;
            if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end())
            {
                if (!channelsMap[strtolower(receiveddata[1])].get_channel_topic().empty())
                    msg = ':' + getServerIp() + " 322 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + int_to_string(channelsMap[strtolower(receiveddata[1])].get_current_users()) + " :" + channelsMap[strtolower(receiveddata[1])].get_channel_topic()+ '\n';
                else 
                    msg = ':' + getServerIp() + " 322 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + int_to_string(channelsMap[strtolower(receiveddata[1])].get_current_users()) + " :\n";
                inv_mssg(sockfd, msg);
            }
        }
    }
    else if (receiveddata.size() == 1){
        for (it = channelsMap.begin(); it != channelsMap.end(); ++it) {
            if (!channelsMap[it->first].get_channel_topic().empty())
                msg = ':' + getServerIp() + " 322 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[it->first].get_original_channel_name() + ' ' + int_to_string(channelsMap[it->first].get_current_users()) + " :" + channelsMap[it->first].get_channel_topic()+ '\n';
            else 
                msg = ':' + getServerIp() + " 322 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[it->first].get_original_channel_name() + ' ' + int_to_string(channelsMap[it->first].get_current_users()) + " :\n";
            inv_mssg(sockfd, msg);
        }
    }
    inv_mssg(sockfd, ':' + getServerIp() + " 323 " + usernickMap[sockfd].get_nickname() + " :End of /LIST\n");
    return ;
}
