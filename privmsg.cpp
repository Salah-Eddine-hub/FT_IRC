/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:16 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/08 12:09:19 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::privmsg(std::vector<std::string> receiveddata, int sockfd){

    if(receiveddata.size() == 1){
        error(sockfd, ":irc_server 411 " + usernickMap[sockfd].get_nickname() + " :No recipient given (PRIVMSG)\n");
        return ;
    }
    if(receiveddata.size() == 2)
        error(sockfd, ":irc_server 412 " + usernickMap[sockfd].get_nickname() + " :No text to send\n");
    else if (receiveddata[1][0] == '#')
    {
        std::string msg = "";
        msg = ':' + usernickMap[sockfd].get_nickname() + "!localhost PRIVMSG " + receiveddata[1] + " :" + receiveddata[2] + '\n';
        if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end())
            channelsMap[strtolower(receiveddata[1])].broadcast(msg , sockfd);
        else        
            error(sockfd, ":irc_server 401 " +usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such nick/channel!\n");
    }
    else if(usernickMap.find(get_sockfd(receiveddata[1])) != usernickMap.end())
    {
        std::string msg;
        msg = ':' + usernickMap[sockfd].get_nickname() + "!localhost PRIVMSG " + receiveddata[1] + " :" + receiveddata[2] + '\n';
        success(get_sockfd(receiveddata[1]), msg);
    }
    else        
        error(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such nick/channel!\n");
    return ;
}
