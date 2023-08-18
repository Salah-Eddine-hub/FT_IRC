/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:33:40 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 23:41:03 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

void Server::list(std::vector<std::string> receiveddata, int sockfd) {

    std::string msg;
    std::map<std::string, Channel>::const_iterator it;

    if (receiveddata.size() != 1){
        error(sockfd, "Error: Wrong number of arguments!\n");
        return ;
    }
    msg = usernickMap[sockfd].get_nickname() + " Channel :Users Name\n";
    success(sockfd, msg);
    for (it = channelsMap.begin(); it != channelsMap.end(); ++it) {
        msg = "Channel Name: " + it->first + '\n';
        success(sockfd, msg);
    }
    return ;
}
