/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:02:41 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/17 13:34:15 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

void Server::quit(int sockfd) {

    for (std::map<std::string, Channel>::iterator it = channelsMap.begin(); it != channelsMap.end();)
    {
        std::string channel_name = it->first;
        if (channelsMap[channel_name].get_is_member(sockfd)){
            channelsMap[channel_name].leave_the_server(sockfd);
            channelsMap[channel_name].broadcast(':' + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + '@' + ClientIp(sockfd) + " QUIT :Quit: " + usernickMap[sockfd].get_nickname() + '\n', -1);
        }
        if (channelsMap[channel_name].get_current_users() == 0)
            it = channelsMap.erase(it);
        else
            ++it;
    }
    inv_mssg(sockfd, "ERROR :Closing Link: " + ClientIp(sockfd) + " (Quit: " + usernickMap[sockfd].get_nickname() + ")\n");
    usernickMap.erase(sockfd);
    close(sockfd);
    return ;
}
