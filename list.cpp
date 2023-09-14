/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:33:40 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/14 13:11:05 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

void Server::list(std::vector<std::string> receiveddata, int sockfd) {

    std::string msg;
    std::map<std::string, Channel>::const_iterator it;

    msg = ":irc_server 321 " + usernickMap[sockfd].get_nickname() + " Channel :Users Name\n";
    inv_mssg(sockfd, msg);
    if (receiveddata.size() > 1) {
        if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end())
        {
            if (!channelsMap[strtolower(receiveddata[1])].get_channel_topic().empty())
                msg = ":irc_server 322 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + int_to_string(channelsMap[strtolower(receiveddata[1])].get_current_users()) + " :" + channelsMap[strtolower(receiveddata[1])].get_channel_topic()+ '\n';
            else 
                msg = ":irc_server 322 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + ' ' + int_to_string(channelsMap[strtolower(receiveddata[1])].get_current_users()) + " :\n";
            inv_mssg(sockfd, msg);
        }
    }
    else if (receiveddata.size() == 1){
        for (it = channelsMap.begin(); it != channelsMap.end(); ++it) {
            if (!channelsMap[it->first].get_channel_topic().empty())
                msg = ":irc_server 322 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[it->first].get_original_channel_name() + ' ' + int_to_string(channelsMap[it->first].get_current_users()) + " :" + channelsMap[it->first].get_channel_topic()+ '\n';
            else 
                msg = ":irc_server 322 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[it->first].get_original_channel_name() + ' ' + int_to_string(channelsMap[it->first].get_current_users()) + " :\n";
            inv_mssg(sockfd, msg);
        }
    }
    inv_mssg(sockfd, ":irc_server 323 " + usernickMap[sockfd].get_nickname() + " :End of /LIST\n");
    return ;
}
