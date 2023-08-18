/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 17:28:18 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::join(std::vector<std::string> receiveddata, int sockfd) {

    if (channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        error(sockfd, "Channel already exists ");
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].second);
    }
    else {
        error(sockfd, "Channel not found!\n");
        success(sockfd, "Success: channel created successfully!\n");
        channelsMap[receiveddata[1]] = Channel(receiveddata[1]);
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].second);
    }
    return ;
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, std::string password, int sockfd) {

    if(check_pass(receiveddata, password, sockfd))
        check_authenticate(sockfd, receiveddata);
    if(receiveddata[0] == "join"){
        if (receiveddata.size() != 2) {
            error(sockfd, "Error: Wrong number of arguments!\n");
            return ;
        }
        if (receiveddata[1][0] != '#') {
            error(sockfd, "Error: Syntax error!\n");
            return ;
        }
        if(this->is_reg == 2)
            join(receiveddata, sockfd);
    }
}
