/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:46:03 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 19:10:32 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::part(std::vector<std::string> receiveddata, int sockfd)
{
    if(receiveddata.size() < 2) {
        error(sockfd, "Error: Not enough parameters!\n");
        return ;
    }
    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        channelsMap[receiveddata[1]].leave_the_channel(sockfd, usernickMap[sockfd].get_nickname());
        if (channelsMap[receiveddata[1]].get_is_operator(sockfd))
            channelsMap[receiveddata[1]].remove_the_operator(sockfd);
    }
    else
        error(sockfd, "Error: No such channel!\n");
    return;
}
