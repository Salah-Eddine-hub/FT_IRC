/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:59:15 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/24 20:35:31 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::kick(std::vector<std::string> receiveddata, int sockfd)
{

    if(receiveddata.size() < 3)
        error(sockfd, "Error: wrong arguments!\n");
    if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    {
        if ()
    }
    else {
        if(usernickMap[sockfd].get_is_mode()) {
            // if channelsMap[];
        }
    }
    return;
}