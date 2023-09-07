/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:52:11 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/06 14:39:01 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::check_pass(std::vector<std::string> receiveddata, int sockfd)
{

    if(!usernickMap[sockfd].get_pwdconf()){
        if(strtolower(receiveddata[0]) != "pass")
            return 0;
        else {
            if(receiveddata.size() != 2)
                return (error(sockfd, "Error: Wrong number of arguments!\n")), 0;
            else {
                if(receiveddata[1] != this->password)
                    return (error(sockfd, "Error: Wrong password!\n")), 0;
                else{
                    success(sockfd, "Success: password correct! Enjoy chatting!\n");
                    usernickMap[sockfd].set_pwdconf(1);
                    return 0;
                }
            }
        }
    }
    return 1;
}
