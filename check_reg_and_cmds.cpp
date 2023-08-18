/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_and_cmds.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:41:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 23:12:01 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include <ctype.h>

void Server::exec_cmds(std::vector<std::string> receiveddata, int sockfd){
    if(receiveddata[0] == "join")
        join(receiveddata, sockfd);
    else if(receiveddata[0] == "list")
        list(receiveddata, sockfd);
    else
        std::cout << "hada makan alkhawa dyali\n";
}

void Server::check_reg_and_cmds(std::vector<std::string> receiveddata, std::string password, int sockfd) {

    if(check_pass(receiveddata, password, sockfd))
        check_authenticate(sockfd, receiveddata);
    exec_cmds(receiveddata, sockfd);
    // if(this->is_reg != 2)
    //     error(sockfd, "Error: PLease confirme your identity before using the server!\n");
    return ;
}
