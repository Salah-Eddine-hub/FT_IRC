/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 22:08:28 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include <ctype.h>


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

    if(!is_valide_name(receiveddata[1], sockfd))
        return ;
    if (channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
    }
    else {
        error(sockfd, "Channel not found!\n");
        success(sockfd, "Success: channel created successfully!\n");
        channelsMap[receiveddata[1]] = Channel();
        channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1]);
    }
    return ;
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, std::string password, int sockfd) {

    if(check_pass(receiveddata, password, sockfd))
        check_authenticate(sockfd, receiveddata);

    // if(this->is_reg != 2)
    //     error(sockfd, "Error: PLease confirme your identity before using the server!\n");
    if(receiveddata[0] == "join"){
        if (receiveddata.size() != 2) {
            error(sockfd, "Error: Wrong number of arguments!\n");
            return ;
        }
        if (receiveddata[1][0] != '#') {
            error(sockfd, "Error: Syntax error!\n");
            return ;
        }
        if(usernickMap[sockfd].get_is_reg() == 2)
            join(receiveddata, sockfd);
    }
    return ;
}
