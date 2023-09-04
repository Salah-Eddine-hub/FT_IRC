/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:19:10 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/04 13:46:11 by iellyass         ###   ########.fr       */
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

    if (receiveddata[1][0] != '#' || receiveddata[1].size() < 2) {
        error(sockfd, "Error: Syntax error!\n");
        return ;
    }
    receiveddata[1] = strtolower(receiveddata[1]);
    if(!is_valide_name(receiveddata[1], sockfd))
        return ;
    if (channelsMap.find(receiveddata[1]) != channelsMap.end()) 
    {
        if (channelsMap[receiveddata[1]].get_is_invite_only() && !usernickMap[sockfd].get_is_invited(receiveddata[1])){
            error(sockfd, "Channel is set to invites only!\n");
            return ;
        }
        if (channelsMap[receiveddata[1]].get_is_pwd_needed().empty() && receiveddata.size() != 2) 
            error(sockfd, "Error: Wrong number of arguments!\n");
        if (!channelsMap[receiveddata[1]].get_is_pwd_needed().empty() && receiveddata.size() < 3 && !channelsMap[receiveddata[1]].get_is_member(sockfd))
            error(sockfd, "Error: Wrong number of arguments. You need a password to join this channel!\n");
        else if (!channelsMap[receiveddata[1]].get_is_pwd_needed().empty() && receiveddata.size() >= 3) 
        {
            std::string pwd;
            for (size_t i = 2; i < receiveddata.size(); i++){
                size_t firstnonspace = receiveddata[i].find_first_not_of(" ");
                    if (firstnonspace != std::string::npos)
                        receiveddata[i] = receiveddata[i].substr(firstnonspace);
                pwd += receiveddata[i] + ' ';
            }            
            pwd.resize(pwd.size() - 1);
            if (channelsMap[receiveddata[1]].get_is_pwd_needed() == pwd)
                channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
            else
                error(sockfd, "Error: Wrong password!\n");
        }
        else
            channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
    }
    else {
        error(sockfd, "Channel not found!\n");
        success(sockfd, "Success: channel created successfully!\n");
        channelsMap[receiveddata[1]] = Channel(receiveddata[1]);
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
        channelsMap[receiveddata[1]].set_is_operator(sockfd);
    }
    
    return ;
}
