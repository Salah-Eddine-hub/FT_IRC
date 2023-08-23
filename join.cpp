/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:19:10 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/23 14:35:42 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::is_valide_name(std::string channel_name, int sockfd){

    for (size_t i = 0; i < channel_name.size() - 1; i++)
    {
        if(!isalnum(channel_name[i + 1]) && channel_name[i + 1] != '_'){
            error(sockfd, "Error: Invalide channel name!\n");
            return 0;
        }
    }
    return 1;
}
void Server::join(std::vector<std::string> receiveddata, int sockfd) {

    if (receiveddata.size() != 2){
        error(sockfd, "Error: Wrong number of arguments!\n");
        return ;
    }
    if (receiveddata[1][0] != '#' || receiveddata[1].size() < 2) {
        error(sockfd, "Error: Syntax error!\n");
        return ;
    }
    if(!is_valide_name(receiveddata[1], sockfd))
        return ;
    if (channelsMap.find(receiveddata[1]) != channelsMap.end())
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
    else {
        error(sockfd, "Channel not found!\n");
        success(sockfd, "Success: channel created successfully!\n");
        channelsMap[receiveddata[1]] = Channel(receiveddata[1]);
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
        usernickMap[sockfd].set_is_mode(1);
    }
    
    return ;
}
