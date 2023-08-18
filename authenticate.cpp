/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authenticate.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/17 22:52:52 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::user_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernickMap[sockfd].first.empty()){
        success(sockfd, "This client is already associated with realname\n");
        return 1;
    }
    if (tokens.size() != 5)
        return (error(sockfd, "Error: USER: wrong number of arguments\n")), 0;
    else{
        this->username = tokens[1];
        this->hostname = tokens[2];
        this->servername = tokens[3];
        this->realname = tokens[4];
        usernickMap[sockfd].first = this->realname;
        std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].first << " " << usernickMap[sockfd].second << std::endl;
    }
    this->is_reg++;
    if(this->is_reg == 2){
        success(sockfd, "Registration completed\n");
        success(sockfd, "use 'cmds' to check the server's commands!\n");    
    }
    return 1;
}

int Server::nick_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernickMap[sockfd].second.empty()){
        success(sockfd, "this client is already associated with nickname\n");
        return 1;
    }
    if (tokens.size() != 2)
        return (error(sockfd, "Error: NICK: wrong number of arguments\n")), 0;
    else{
        this->nickname = tokens[1];
        usernickMap[sockfd].second = this->nickname;
        std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].first << " " << usernickMap[sockfd].second << std::endl;
    }
    this->is_reg++;
    if(this->is_reg == 2){
        success(sockfd, "Registration completed\n");
        success(sockfd, "use 'cmds' to check the server's commands!\n");    
    }
    return 1;
}

int Server::check_authenticate(int sockfd, std::vector<std::string> tokens)
{
    std::map<int, std::pair<std::string, std::string> >::iterator it;

    it = this->usernickMap.find(sockfd);
    if (!tokens.empty() && tokens[0] == "USER")
        user_cmd(sockfd, tokens);
    else if (!tokens.empty() && tokens[0] == "NICK")
        nick_cmd(sockfd, tokens);
    return 1;
}
