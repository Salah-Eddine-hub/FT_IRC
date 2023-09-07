/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:33:40 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/05 20:06:02 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

//list + arg
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
