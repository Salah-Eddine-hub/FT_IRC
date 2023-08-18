/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:52:11 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/17 21:50:42 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::check_pass(std::vector<std::string> receiveddata, std::string password, int sockfd)
{

    
    if(this->password != 1){
        if(receiveddata[0] != "pass"){
            error(sockfd, "Error: please use 'pass' command to enter the password and have full access of the server's channels and commands!\n");
            return 0;
        }
        else {
            if(receiveddata.size() != 2)
                return (error(sockfd, "Error: Wrong number of arguments!\n")), 0;
            else {
                if(receiveddata[1] != password)
                    return (error(sockfd, "Error: Wrong password!\n")), 0;
                else{
                    error(sockfd, "Success: password correct! Enjoy chatting!\n");
                    this->password = 1;
                }
            }
        }
    }
    return 1;
}
