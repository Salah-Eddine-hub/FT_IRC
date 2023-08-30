/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:16 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 13:53:50 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::privmsg(std::vector<std::string> receiveddata, int sockfd){

    if(receiveddata.size() < 3)
        error(sockfd, "Error: wrong arguments!\n");
    if (receiveddata[1][0] == '#')
    {
        if (channelsMap.find(receiveddata[1]) != channelsMap.end())
            channelsMap[receiveddata[1]].broadcast(usernickMap[sockfd].get_nickname() + " sent a message from " + receiveddata[1] + " channel: " + receiveddata[2] + '\n', sockfd);
        else        
            error(sockfd, "Error: channel not found!\n");
    }
    else if(usernickMap.find(get_sockfd(receiveddata[1])) != usernickMap.end())
    {
        std::string msg;
        // for (size_t j = 2; j < receiveddata.size() ; j++){
        //     size_t firstnonspace = receiveddata[j].find_first_not_of(" ");
        //     if (firstnonspace != std::string::npos)
        //         receiveddata[j] = receiveddata[j].substr(firstnonspace);
        //     msg += receiveddata[j] + ' ';
        // }
        // msg.resize(msg.size() - 1);
        msg = "You received message from " + usernickMap[sockfd].get_nickname() + ": " + receiveddata[2] + '\n';
        success(get_sockfd(receiveddata[1]), msg);
    }
    else        
        error(sockfd, "Error: User not found!\n");
    return ;
}
