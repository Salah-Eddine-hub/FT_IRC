/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/06 13:45:34 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include <ctype.h>


int Server::all_cmds(std::vector<std::string> receiveddata, int sockfd) 
{
    if ((strtolower(receiveddata[0]) == "join" || strtolower(receiveddata[0]) == "nick" || strtolower(receiveddata[0]) == "user"
        || strtolower(receiveddata[0]) == "privmsg"|| strtolower(receiveddata[0]) == "kick" || strtolower(receiveddata[0]) == "invite"
             || strtolower(receiveddata[0]) == "topic" || strtolower(receiveddata[0]) == "mode" || strtolower(receiveddata[0]) == "part") 
                && receiveddata.size() < 2){
        error(sockfd, "irc_server 461 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Not enough parameters\n");
        return 0;
    }
    return 1;
}

void Server::exec_cmds(std::vector<std::string> receiveddata, int sockfd){
    
    if (usernickMap[sockfd].get_nickname().empty() || usernickMap[sockfd].get_realname().empty())
    {
        if(strtolower(receiveddata[0]) == "user")
            user(receiveddata, sockfd);
        else if(strtolower(receiveddata[0]) == "nick")
            nick(receiveddata, sockfd);
        else {
            if (usernickMap[sockfd].get_nickname().empty())
                error(sockfd, "irc_server 451 * " + receiveddata[0] + " :You must finish connecting with another nickname first\n");
            else
                error(sockfd, "irc_server 451 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :You must finish connecting with another nickname first\n");
            return ;
        }
        std::cout << "usernickMap[sockfd].get_realname()   :" << usernickMap[sockfd].get_realname() << std::endl; 
    }
    else if (!usernickMap[sockfd].get_nickname().empty() && !usernickMap[sockfd].get_realname().empty())
    {
        // usernickMap[sockfd].set_is_reg(1);
        // if (!all_cmds(receiveddata, sockfd))
        //     return ;
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
        else if(strtolower(receiveddata[0]) == "bot")
            DisplayTime(receiveddata[1], sockfd);
        else
            error(sockfd, "irc_server 421 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[0] + " :Unknown command\n");
    }
        std::cout << "usernickMap[sockfd].get_nickname()   :" << usernickMap[sockfd].get_nickname() << std::endl; 
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd) {

    if(check_pass(receiveddata, sockfd))
        exec_cmds(receiveddata, sockfd);    
    return ;
}
