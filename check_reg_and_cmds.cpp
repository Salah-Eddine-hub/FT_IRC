/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/07 16:12:34 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include <ctype.h>

void Server::exec_cmds(std::vector<std::string> receiveddata, int sockfd){
    
    if (usernickMap[sockfd].get_nickname().empty() || usernickMap[sockfd].get_realname().empty())
    {
        if(strtolower(receiveddata[0]) == "user")
            user(receiveddata, sockfd);
        else if(strtolower(receiveddata[0]) == "nick")
            nick(receiveddata, sockfd);
        else {
            if (usernickMap[sockfd].get_nickname().empty())
                error(sockfd, ":irc_server 451 * " + receiveddata[0] + " :You must finish connecting with another nickname first\n");
            else
                error(sockfd, ":irc_server 451 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :You must finish connecting with another nickname first\n");
            return ;
        }
    }
    else if (!usernickMap[sockfd].get_nickname().empty() && !usernickMap[sockfd].get_realname().empty())
    {
        usernickMap[sockfd].set_is_reg(1);
        if(strtolower(receiveddata[0]) == "join")
            join(receiveddata, sockfd);
        else if(strtolower(receiveddata[0]) == "nick")
            nick(receiveddata, sockfd);
        else if(strtolower(receiveddata[0]) == "user")
            user(receiveddata, sockfd);
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
            error(sockfd, ":irc_server 421 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Unknown command\n");
    }
        std::cout << "usernickMap[sockfd].get_nickname()   :" << usernickMap[sockfd].get_nickname() << std::endl; 
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd) {

    if(check_pass(receiveddata, sockfd))
        exec_cmds(receiveddata, sockfd);    
    return ;
}
