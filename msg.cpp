/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:59:43 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/24 18:46:54 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::msg(std::vector<std::string> receiveddata, int sockfd){

    std::string message;

    if(receiveddata.size() >= 3){
        if (channelsMap.find(receiveddata[1]) != channelsMap.end()) {
            for (size_t i = 2; i < receiveddata.size(); i++){
                size_t firstnonspace = receiveddata[i].find_first_not_of(" ");
                    if (firstnonspace != std::string::npos)
                        receiveddata[i] = receiveddata[i].substr(firstnonspace);
                message += receiveddata[i] + ' ';
            }
            message[message.size() - 1] = '\n';
            channelsMap[receiveddata[1]].broadcast(usernickMap[sockfd].get_nickname() + " sent a message from " + receiveddata[1] + " channel: " + message, sockfd);
        } 
        else 
            error(sockfd, "Error: Channel not found!\n");
    }
    else 
        error(sockfd, "Error: wrong arguments!\n");
    return ;
}
