/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 17:13:22 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include <ctype.h>

void Server::exec_cmds(std::vector<std::string> receiveddata, int sockfd){
    if(usernickMap[sockfd].get_is_reg() != 2)
        return ;
    if(strtolower(receiveddata[0]) == "join")
        join(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "list")
        list(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "privmsg")
        privmsg(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "kick")
        kick(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "invite")
        invite(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "topic")
        topic(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "mode")
        mode(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "part")
        part(receiveddata, sockfd);
    else
        error(sockfd, receiveddata[0] + " :Unknown command\n");
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd) {

    if(check_pass(receiveddata, sockfd))
        check_authenticate(sockfd, receiveddata);
    exec_cmds(receiveddata, sockfd);
    return ;
}
