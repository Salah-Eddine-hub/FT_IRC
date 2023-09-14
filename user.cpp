/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:11:49 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/14 14:04:11 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"


int Server::is_valide_username(std::string nickname)
{
    int i = 0;
    while (nickname[i])
    {
        if (!isalnum(nickname[i]) && nickname[i] != '_')
            return 0 ;
        i ++;
    }
    return 1;
}

void Server::user(std::vector<std::string> receiveddata, int sockfd) {

    if (receiveddata.size() < 5){
        inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " USER :Not enough parameters\n");
        return ;
    }
    if (usernickMap[sockfd].get_is_reg())
    {
        inv_mssg(sockfd, ":irc_server 462 " + usernickMap[sockfd].get_nickname() + " :You may not reregister\n");
        return ;
    }
    else{
        if (is_valide_username(receiveddata[1])) {
            usernickMap[sockfd].set_username(receiveddata[1]);
            usernickMap[sockfd].set_hostname(receiveddata[2]);
            usernickMap[sockfd].set_servername(receiveddata[3]);
            usernickMap[sockfd].set_realname(receiveddata[4]);
        }
        else
            inv_mssg(sockfd, "ERROR :Invalid username\n");
    }
    return ;
}
