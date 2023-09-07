/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authenticate.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/05 13:39:26 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

// int Server::user_cmd(int sockfd, std::vector<std::string> tokens)
// {
//     if (tokens.size() != 5)
//         return (error(sockfd, "Error: USER: wrong number of arguments\n")), 0;
//     if(!usernickMap[sockfd].get_realname().empty()) {
//         success(sockfd, "This client is already associated with realname\n");
//         return 1;
//     }
//     else{
//         usernickMap[sockfd].set_username(tokens[1]);
//         usernickMap[sockfd].set_hostname(tokens[2]);
//         usernickMap[sockfd].set_servername(tokens[3]);
//         usernickMap[sockfd].set_realname(tokens[4]);
//         std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].get_realname() << " " << usernickMap[sockfd].get_nickname() << std::endl;
//     }
//     usernickMap[sockfd].set_is_reg();
//     if(usernickMap[sockfd].get_is_reg() == 2){
//         success(sockfd, "Registration completed\n");
//         success(sockfd, "use 'cmds' to check the server's commands!\n");    
//     }
//     return 1;
// }

// int Server::nick_cmd(int sockfd, std::vector<std::string> tokens)
// {
//     std::map<int, Client>::iterator it;
//     if (tokens.size() != 2)
//         return (error(sockfd, "Error: NICK: wrong number of arguments\n")), 0;
//     if(!usernickMap[sockfd].get_nickname().empty()) {
//         success(sockfd, "this client is already associated with nickname\n");
//         return 1;
//     }
//     else{
//         for (it = usernickMap.begin(); it != usernickMap.end(); it++){
//             if(it->second.get_nickname() == tokens[1])
//                 return (error(sockfd, "Error: Nickname already associated with another user\n")), 0;
//         }
//         usernickMap[sockfd].set_nickname(tokens[1]);
//         std::cout << "usernickMap[sockfd]: " << usernickMap[sockfd].get_realname() << " " << usernickMap[sockfd].get_nickname() << std::endl;
//     }
//     usernickMap[sockfd].set_is_reg();
//     if(usernickMap[sockfd].get_is_reg() == 2){
//         success(sockfd, "Registration completed\n");
//         success(sockfd, "use 'cmds' to check the server's commands!\n");    
//     }
//     return 1;
// }

int Server::check_authenticate(int sockfd, std::vector<std::string> tokens)
{
    if (usernickMap[sockfd].get_is_reg() != 2 && usernickMap[sockfd].get_pwdconf()) {
        if(usernickMap[sockfd].get_is_reg() != 2 && (tokens[0] != "user" && tokens[0] != "nick"))
            error(sockfd, "Please confirme your identity first by using 'USER' and 'NICK' commands\n");
        if (!tokens.empty() && strtolower(tokens[0]) == "user")
            user(tokens, sockfd);
        else if (!tokens.empty() && strtolower(tokens[0]) == "nick")
            nick(tokens, sockfd);
    }
    return 1;
}
