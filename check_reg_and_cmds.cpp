/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/29 15:35:40 by iellyass         ###   ########.fr       */
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
            // wa9ila khass gha 3rd arg bo7do li ytssift
    else if(strtolower(receiveddata[0]) == "msg")
        msg(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "kick")
        kick(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "invite")
        invite(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "topic")
        topic(receiveddata, sockfd);
    else if(strtolower(receiveddata[0]) == "mode")
        mode(receiveddata, sockfd);
    else
        std::cout << "hada makan alkhawa dyali\n";
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd) {

    if(check_pass(receiveddata, sockfd))
        check_authenticate(sockfd, receiveddata);
    exec_cmds(receiveddata, sockfd);
    return ;
}
