/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:11:06 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/05 16:29:50 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::is_valide_nickname(std::string &nickname, int sockfd)
{
    int i = 0;
    std::string holder = "";

    if ((nickname[0] < 'a' || nickname[0] > 'z') && nickname[0] != '_') {
        if(usernickMap[sockfd].get_nickname().empty())
            error(sockfd, "irc_server 432 "+ nickname +" :Erroneous Nickname\n");
        else
            error(sockfd, "irc_server 432 " + usernickMap[sockfd].get_nickname() + ' ' + nickname + " :Erroneous Nickname\n");
        return 0;
    }
    while ((nickname[i] >= 'a' && nickname[i] <= 'z') || nickname[i] == '_' || isdigit(nickname[i])) {
        holder += nickname[i];
        i++;
    }
    nickname = holder;
    return 1;
}

void Server::nick(std::vector<std::string> receiveddata, int sockfd) {

    std::map<int, Client>::iterator it;
    if (receiveddata.size() < 2){
        if (!usernickMap[sockfd].get_nickname().empty())
            error(sockfd, "irc_server 431 " + usernickMap[sockfd].get_nickname() + " :No nickname given\n");
        else
            error(sockfd, "irc_server 431  :No nickname given\n");
        return ;
    }
    else{
        for (it = usernickMap.begin(); it != usernickMap.end(); it++){
            if(it->second.get_nickname() == receiveddata[1]) {
                if(usernickMap[sockfd].get_nickname().empty()){
                    error(sockfd, "irc_server 433 * " + receiveddata[1] + " :Nickname is already in use.\n");
                    return ;
                }
                else if(usernickMap[sockfd].get_nickname() == receiveddata[1])
                    return ;
                else
                    error(sockfd, "irc_server 433 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :Nickname is already in use.\n");
                return ;
            }
        }
        if (is_valide_nickname(receiveddata[1], sockfd))
            usernickMap[sockfd].set_nickname(receiveddata[1]);
    }
    return ;
}
