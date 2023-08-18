/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authenticate.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 22:31:09 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::user_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernickMap[sockfd].get_realname().empty()){
        success(sockfd, "This client is already associated with realname\n");
        return 1;
    }
    if (tokens.size() != 5)
        return (error(sockfd, "Error: USER: wrong number of arguments\n")), 0;
    else{
        usernickMap[sockfd].set_username(tokens[1]);
        usernickMap[sockfd].set_hostname(tokens[2]);
        usernickMap[sockfd].set_servername(tokens[3]);
        usernickMap[sockfd].set_realname(tokens[4]);
        std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].get_realname() << " " << usernickMap[sockfd].get_nickname() << std::endl;
    }
    usernickMap[sockfd].inc_is_reg();
    if(usernickMap[sockfd].get_is_reg() == 2){
        success(sockfd, "Registration completed\n");
        success(sockfd, "use 'cmds' to check the server's commands!\n");    
    }
    return 1;
}

int Server::nick_cmd(int sockfd, std::vector<std::string> tokens)
{
    if(!usernickMap[sockfd].get_nickname().empty()){
        success(sockfd, "this client is already associated with nickname\n");
        return 1;
    }
    if (tokens.size() != 2)
        return (error(sockfd, "Error: NICK: wrong number of arguments\n")), 0;
    else{
        usernickMap[sockfd].set_nickname(tokens[1]);
        std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].get_realname() << " " << usernickMap[sockfd].get_nickname() << std::endl;
    }
    usernickMap[sockfd].inc_is_reg();
    if(usernickMap[sockfd].get_is_reg() == 2){
        success(sockfd, "Registration completed\n");
        success(sockfd, "use 'cmds' to check the server's commands!\n");    
    }
    return 1;
}

int Server::check_authenticate(int sockfd, std::vector<std::string> tokens)
{
    if (usernickMap[sockfd].get_is_reg() != 2 && usernickMap[sockfd].get_pwdconf()) {
        std::cout << "this->is_reg: " << usernickMap[sockfd].get_is_reg() << std::endl;
        if(usernickMap[sockfd].get_is_reg() != 2 && (tokens[0] != "USER" && tokens[0] != "NICK"))
            error(sockfd, "Please confirme your identity first by using 'USER' and 'NICK' commands\n");
        if (!tokens.empty() && tokens[0] == "USER")
            user_cmd(sockfd, tokens);
        else if (!tokens.empty() && tokens[0] == "NICK")
            nick_cmd(sockfd, tokens);
    }
    return 1;
}
