/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authenticate.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/15 18:17:12 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::user_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernameMap[sockfd].first.empty()){
        std::cout << "sockfd " << sockfd << " is already associated with realname: " << usernameMap[sockfd].first << std::endl;
        return 1;
    }
    if (tokens.size() != 5)
        return (std::cout << "USER:: wrong number of arguments" << std::endl), 0;
    else{
        this->username = tokens[1];
        this->hostname = tokens[2];
        this->servername = tokens[3];
        this->realname = tokens[4];
        usernameMap[sockfd].first = this->realname;
        std::cout << "usernameMap[sockfd]: " << usernameMap[sockfd].first << " " << usernameMap[sockfd].second << std::endl;
    }
    this->is_reg++;
    return 1;
}

int Server::nick_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernameMap[sockfd].second.empty()){
        std::cout << "sockfd " << sockfd << " is already associated with nickname: " << usernameMap[sockfd].second << std::endl;
        return 1;
    }
    if (tokens.size() != 2)
        return (std::cout << "USER:: wrong number of arguments" << std::endl), 0;
    else{
        this->nickname = tokens[1];
        usernameMap[sockfd].second = this->nickname;
        std::cout << "usernameMap[sockfd]: " << usernameMap[sockfd].first << " " << usernameMap[sockfd].second << std::endl;
    }
    this->is_reg++;
    return 1;
}

int Server::check_authenticate(int sockfd, std::string buffer)
{
    std::map<int, std::pair<std::string, std::string> >::iterator it;
    std::vector<std::string> tokens;
    std::istringstream iss(buffer);
    std::string holder;

    std::cout << "this->is_reg: " << this->is_reg << std::endl;
    it = this->usernameMap.find(sockfd);
    if (it == usernameMap.end() || it->second.first.empty() || it->second.second.empty()) {
    while (std::getline(iss, holder, ' ')) {
        if (!holder.empty()) {
            if (holder.back() == '\n')
                holder.pop_back();
//------------------------------------------------------------------------------------------------ version c++98
            // if (!holder.empty() && holder[holder.length() - 1] == '\n')
            //     holder.resize(holder.length() - 1);
//------------------------------------------------------------------------------------------------ version c++98
            tokens.push_back(holder);
        }
    }
    if (!tokens.empty() && tokens[0] == "USER")
        user_cmd(sockfd, tokens);
    else if (!tokens.empty() && tokens[0] == "NICK")
        nick_cmd(sockfd, tokens);
    }
    if(this->is_reg == 2)
        std::cout << "Registration completed" << std::endl;
    return 1;
}
