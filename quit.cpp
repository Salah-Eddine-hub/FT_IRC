/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:02:41 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/17 10:59:23 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"server.hpp"

void Server::quit(int sockfd) {

    (void) sockfd;

    // for (std::map<std::string, Channel>::iterator it = channelsMap.begin(); it != channelsMap.end();)
    // {
    //     std::string channel_name = it->first;
    //     if (channelsMap[channel_name].get_is_member(fds[i].fd)){
    //         channelsMap[channel_name].leave_the_server(fds[i].fd);
    //         channelsMap[channel_name].broadcast(':' + usernickMap[sockfd].get_nickname() + "!~" + usernickMap[sockfd].get_username() + "@lcoalhost QUIT :Quit: " + usernickMap[sockfd].get_nickname() + '\n', -1);
    //         inv_mssg(sockfd, "ERROR :Closing Link: ClientIp(sockfd) (Quit: " + usernickMap[sockfd].get_nickname() + ")\n");
    //     }
    //     if (channelsMap[channel_name].get_current_users() == 0){
    //         it = channelsMap.erase(it);
    //     }
    //     else
    //         ++it;
    // }
    // usernickMap.erase(fds[i].fd);
    // close(fds[i].fd);
    // exit (1) ;
}
